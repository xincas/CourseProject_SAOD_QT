#include "flightform.h"
#include "ui_flightform.h"

FlightForm::FlightForm(Flight curFly,
                       AVL<Flight>* flys,
                       List<Ticket>* ticks,
                       /*Ticket* tickets, int n_t,*/
                       HashTable<std::string, Passanger>* passes,
                       QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlightForm)
{
    ui->setupUi(this);

    this->fly_ = curFly;
    /*this->tickets_ = tickets;
    this->n_tick = n_t;*/
    this->ticks = ticks;
    this->passes_ = passes;
    this->flys = flys;

    fillForms();
    createTable();
    refreshTable();
}

FlightForm::~FlightForm()
{
    emit destroyed();
    //delete[] tickets_;
    delete ui;
}

void FlightForm::createTable()
{
    ui->tableWidget->clear();

    QStringList a = QStringList() << "Номер билета"
                                  << "Номер паспорта"
                                  << "ФИО";

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels(a);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void FlightForm::refreshTable()
{
    ui->tableWidget->clearContents();
    int rows = ui->tableWidget->rowCount();

    int t_size = 0;
    Ticket* flight_tickets = ticketsOfFlight(fly_.flight_number, &t_size);

    if(rows < t_size)
    {
        for(; rows < t_size; rows++)
            ui->tableWidget->insertRow(rows);
    }
    else if (rows > t_size)
    {
        while (rows > t_size)
            ui->tableWidget->removeRow(--rows);
    }

    if (flight_tickets != nullptr)
    {
        for (int i = 0; i < t_size; i++)
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::fromUtf8((*(flight_tickets + i)).ticket_number.c_str())));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromUtf8(passes_->operator[](flight_tickets[i].passport_number).passport_number.c_str())));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::fromUtf8(passes_->operator[](flight_tickets[i].passport_number).full_name.c_str())));
        }
    }

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
}

void FlightForm::fillForms()
{
    ui->line_num->setText(QString::fromUtf8(fly_.flight_number));
    ui->line_name->setText(QString::fromUtf8(fly_.airline_name));
    ui->line_a_from->setText(QString::fromUtf8(fly_.a_from));
    ui->line_a_to->setText(QString::fromUtf8(fly_.a_to));
    ui->line_date->setText(QString::fromUtf8(fly_.date));
    ui->line_time->setText(QString::fromUtf8(fly_.time));
    ui->line_all_seats->setText(QString::number(fly_.all_seats));
    ui->line_free_seats->setText(QString::number(fly_.free_seats));
}

Ticket* FlightForm::ticketsOfFlight(std::string fly_num, int* size)
{
    Ticket* tickets = ticks->getAll();
    int size_all = ticks->size();
    *size = 0;
    Ticket* tmp = new Ticket[size_all];

    for (int i = 0; i < size_all; i++)
        if (fly_num == tickets[i].flight_number)
            tmp[(*size)++] = tickets[i];

    Ticket* pas_tic = new Ticket[*size];
    for (int i = 0; i < (*size); i++)
        pas_tic[i] = tmp[i];

    delete[] tickets;
    delete[] tmp;
    if (*size == 0)
    {
        delete[] pas_tic;
        return nullptr;
    }
    return pas_tic;
}

void FlightForm::refreshTickets(/*Flight fly, Ticket* tickets, int n_t*/)
{
    /*delete[] this->tickets_;
    this->tickets_ = tickets;
    this->n_tick = n_t;*/

    if (flys->contains(fly_))
    {
        Flight tmp = flys->get(fly_);
        this->fly_ = tmp;

        refreshTable();
        fillForms();
    }
    else
        this->close();
}
