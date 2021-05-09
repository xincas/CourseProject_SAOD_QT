#include "passform.h"
#include "ui_passform.h"

PassForm::PassForm(Passanger curPas,
                   List<Ticket>* ticks,
                   /*Ticket* tickets, int n_t,*/
                   AVL<Flight>* flight,
                   QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PassForm)
{
    this->pas_ = curPas;
    /*this->tickets_ = tickets;
    this->n_tick = n_t;*/
    this->ticks = ticks;
    this->fligths = flight;

    ui->setupUi(this);

    fillForms();
    createTableTickets();
    refreshTableTickets();
    createTablePurchase();
    refreshTablePurchase();
}

PassForm::~PassForm()
{
    emit destroyed();
    //delete[] tickets_;
    delete ui;
}

void PassForm::createTableTickets()
{
    ui->tableWidget->clear();

    QStringList a = QStringList() << "Номер билета"
                                  << "Номер рейса"
                                  << "Дата";

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels(a);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void PassForm::createTablePurchase()
{
    ui->tableWidget_2->clear();

    QStringList a = QStringList() << "Номер рейса"
                                  << "Откуда"
                                  << "Куда"
                                  << "Дата, время";

    ui->tableWidget_2->setColumnCount(4);
    ui->tableWidget_2->setShowGrid(true);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_2->setHorizontalHeaderLabels(a);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void PassForm::refreshTableTickets()
{
    ui->tableWidget->clearContents();
    int rows = ui->tableWidget->rowCount();

    int t_size = 0;
    Ticket* pas_tickets = ticketsOfPass(pas_.passport_number, &t_size);

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

    if (pas_tickets != nullptr)
    {
        for (int i = 0; i < t_size; i++)
        {
            Flight com = Flight(pas_tickets[i].flight_number);
            Flight dada = fligths->get(com);
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::fromUtf8((*(pas_tickets + i)).ticket_number.c_str())));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromUtf8(dada.flight_number.c_str())));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::fromUtf8(dada.date.c_str())));
        }
    }

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
}

void PassForm::refreshTablePurchase()
{
    ui->tableWidget_2->clearContents();
    int rows = ui->tableWidget_2->rowCount();
    Flight* flys = fligths->getAll();
    int size = fligths->size();

    if(rows < size)
    {
        for(; rows < size; rows++)
            ui->tableWidget_2->insertRow(rows);
    }
    else if (rows > size)
    {
        while (rows > size)
            ui->tableWidget_2->removeRow(--rows);
    }

    for (int i = 0; i < size; i++)
    {
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(QString::fromUtf8(flys[i].flight_number.c_str())));
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(QString::fromUtf8(flys[i].a_from.c_str())));
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(QString::fromUtf8(flys[i].a_to.c_str())));
        ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(QString::fromUtf8((flys[i].date + " " + flys[i].time).c_str())));
    }

    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    delete[] flys;
}

void PassForm::fillForms()
{
    ui->line_name->setText(QString::fromUtf8(pas_.full_name));
    ui->line_birth->setText(QString::fromUtf8(pas_.birth_date));
    ui->line_pas_num->setText(QString::fromUtf8(pas_.passport_number));
    ui->line_birth_2->setText(QString::fromUtf8(pas_.issue_date));
}

Ticket* PassForm::ticketsOfPass(std::string pas_num, int* pas_size)
{
    Ticket* tickets = ticks->getAll();
    int size_all = ticks->size();
    *pas_size = 0;
    Ticket* tmp = new Ticket[size_all];

    for (int i = 0; i < size_all; i++)
        if (pas_num == tickets[i].passport_number)
            tmp[(*pas_size)++] = tickets[i];

    Ticket* pas_tic = new Ticket[*pas_size];
    for (int i = 0; i < (*pas_size); i++)
        pas_tic[i] = tmp[i];

    delete[] tickets;
    delete[] tmp;
    if (*pas_size == 0)
    {
        delete[] pas_tic;
        return nullptr;
    }
    return pas_tic;
}

void PassForm::on_issue_ticket_but_clicked()
{
    if (ui->tableWidget_2->selectedItems().isEmpty())
        return;

    int row = ui->tableWidget_2->selectedItems().first()->row();

    Flight tmp = Flight(ui->tableWidget_2->item(row, 0)->text().toStdString());

    emit issueNewTicket(tmp);
}

void PassForm::on_return_ticket_but_clicked()
{
    if (ui->tableWidget->selectedItems().isEmpty())
        return;

    int row = ui->tableWidget->selectedItems().first()->row();

    emit returnTicket(Ticket(ui->tableWidget->item(row, 0)->text().toStdString()));
}

void PassForm::refreshTickets(/*Ticket* tickets, int n_t*/)
{
    /*delete[] tickets_;
    this->tickets_ = tickets;
    this->n_tick = n_t;*/

    refreshTableTickets();
}

Passanger PassForm::getCurPass()
{
    return this->pas_;
}
