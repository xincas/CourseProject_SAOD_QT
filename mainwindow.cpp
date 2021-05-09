#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Passes.add("3314-335370", Passanger("3314-335370", "Rakhim Zinatov", "02.03.2001","Vyatskie Polyani"));
    Passes.add("1314-335370", Passanger("1314-335370", "Ismail Akmanov", "25.08.2001", "Naberezhnye Chelny"));
    Passes.add("2314-335370", Passanger("2314-335370", "Mikhail Nesterenko", "22.06.2001", "Saint-Petersburg"));
    Passes.add("4314-335370", Passanger("4314-335370", "Alexander Krutov", "15.11.2001", "Saint-Petersburg"));

    Flights.add(Flight("RUS-598", "RussiaAirlines", "Moscow", "Saint-Petersburg", "30.04.2021", "12:52", 20, 10));
    Flights.add(Flight("GER-125", "GermanyAirlines", "Berlin", "Moscow", "30.04.2021", "07:25", 20, 5));
    Flights.add(Flight("UKR-276", "UkraineAirlines", "Kiev", "Moscow", "30.04.2021", "00:38", 20, 1));

    Tickets.push_back(Ticket("3314-335370", "RUS-598", "125936526"));
    Tickets.push_back(Ticket("3314-335370", "GER-125", "125683526"));
    Tickets.push_back(Ticket("3314-335370", "UKR-276", "525683526"));
    Tickets.push_back(Ticket("1314-335370", "RUS-598", "122346526"));
    Tickets.push_back(Ticket("4314-335370", "RUS-598", "235636526"));
    Tickets.push_back(Ticket("2314-335370", "RUS-598", "121546526"));

    createPassengersTable();
    createFlightsTable();
    createTicketsTable();

    refreshFlightTable();
    refreshPassTable();
    refreshTickTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createPassengersTable()
{
    ui->tab_pass->clear();

    QStringList a = QStringList() << "Номер паспорта"
                                  << "ФИО"
                                  << "Дата рождения"
                                  << "Место выдачи паспорта";

    ui->tab_pass->setColumnCount(4);
    ui->tab_pass->setShowGrid(true);
    ui->tab_pass->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_pass->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_pass->setHorizontalHeaderLabels(a);
    ui->tab_pass->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::createTicketsTable()
{
    ui->tab_tickets->clear();

    QStringList a = QStringList() << "Номер билета"
                                  << "Номер паспорта пассажира"
                                  << "Номер авиарейса";

    ui->tab_tickets->setColumnCount(3);
    ui->tab_tickets->setShowGrid(true);
    ui->tab_tickets->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_tickets->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_tickets->setHorizontalHeaderLabels(a);
    ui->tab_tickets->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::createFlightsTable()
{
    ui->tab_flight->clear();

    QStringList a = QStringList() << "Номер авиарейса"
                                  << "Название авиакомпании"
                                  << "Время вылета"
                                  << "Аэропорт отправления"
                                  << "Аэропорт прибытия";

    ui->tab_flight->setColumnCount(5);
    ui->tab_flight->setShowGrid(true);
    ui->tab_flight->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_flight->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_flight->setHorizontalHeaderLabels(a);
    ui->tab_flight->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::refreshPassTable(Passanger* f_pass, int f_size)
{
    ui->tab_pass->clearContents();
    int rows = ui->tab_pass->rowCount();
    Passanger* passes;
    int n;

    if (!f_pass)
    {
        passes = Passes.getAll();
        n = Passes.getSize();
    }
    else
    {
        passes = f_pass;
        n = f_size;
    }

    if(rows < n)
    {
        for(; rows < n; rows++)
            ui->tab_pass->insertRow(rows);
    }
    else if (rows > n)
    {
        while (rows > n)
            ui->tab_pass->removeRow(--rows);
    }


    if (passes != nullptr)
    {
        for (int i = 0; i < n; i++)
        {
            ui->tab_pass->setItem(i,0,new QTableWidgetItem(QString::fromUtf8((*(passes + i)).passport_number.c_str())));
            ui->tab_pass->setItem(i,1,new QTableWidgetItem(QString::fromUtf8((*(passes + i)).full_name.c_str())));
            ui->tab_pass->setItem(i,2,new QTableWidgetItem(QString::fromUtf8((*(passes + i)).birth_date.c_str())));
            ui->tab_pass->setItem(i,3,new QTableWidgetItem(QString::fromUtf8((*(passes + i)).issue_date.c_str())));
        }
    }

    ui->tab_pass->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tab_pass->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tab_pass->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    delete[] passes;
}

void MainWindow::refreshTickTable(Ticket* f_tick, int t_size)
{
    ui->tab_tickets->clearContents();
    int rows = ui->tab_tickets->rowCount();
    Ticket* tickets;
    int n;

    if (!f_tick)
    {
        tickets = Tickets.getAll();
        n = Tickets.size();
    }
    else
    {
        tickets = f_tick;
        n = t_size;
    }

    if(rows < n)
    {
        for(; rows < n; rows++)
            ui->tab_tickets->insertRow(rows);
    }
    else if (rows > n)
    {
        while (rows > n)
            ui->tab_tickets->removeRow(--rows);
    }


    if (tickets != nullptr)
    {
        for (int i = 0; i < n; i++)
        {
            ui->tab_tickets->setItem(i,0,new QTableWidgetItem(QString::fromUtf8(tickets[i].ticket_number.c_str())));
            ui->tab_tickets->setItem(i,1,new QTableWidgetItem(QString::fromUtf8(tickets[i].passport_number.c_str())));
            ui->tab_tickets->setItem(i,2,new QTableWidgetItem(QString::fromUtf8(tickets[i].flight_number.c_str())));
        }
    }

    ui->tab_tickets->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tab_tickets->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    delete[] tickets;
}

void MainWindow::refreshFlightTable(Flight* f_flights, int f_size)
{
    ui->tab_flight->clearContents();
    int rows = ui->tab_flight->rowCount();
    Flight* flights;
    int n;

    if (!f_flights)
    {
        flights = Flights.getAll();
        n = Flights.size();
    }
    else
    {
        flights = f_flights;
        n = f_size;
    }

    if(rows < n)
    {
        for(; rows < n; rows++)
            ui->tab_flight->insertRow(rows);
    }
    else if (rows > n)
    {
        while (rows > n)
            ui->tab_flight->removeRow(--rows);
    }

    if (flights != nullptr)
    {
        for (int i = 0; i < n; i++)
        {
            ui->tab_flight->setItem(i,0,new QTableWidgetItem(QString::fromUtf8(flights[i].flight_number.c_str())));
            ui->tab_flight->setItem(i,1,new QTableWidgetItem(QString::fromUtf8(flights[i].airline_name.c_str())));
            ui->tab_flight->setItem(i,2,new QTableWidgetItem(QString::fromUtf8(flights[i].time.c_str())));
            ui->tab_flight->setItem(i,3,new QTableWidgetItem(QString::fromUtf8(flights[i].a_from.c_str())));
            ui->tab_flight->setItem(i,4,new QTableWidgetItem(QString::fromUtf8(flights[i].a_to.c_str())));
        }
    }

    ui->tab_flight->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tab_flight->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tab_flight->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tab_flight->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);

    delete[] flights;
}



void MainWindow::on_add_pass_but_clicked()
{
    UserAddWindow = new UserAddForm();
    UserAddWindow->setAttribute(Qt::WA_DeleteOnClose);

    connect(UserAddWindow, SIGNAL(pressed_add()), this, SLOT(addPassanger()));

    UserAddWindow->show();
}

void MainWindow::addPassanger()
{
    Passanger n_pass = UserAddWindow->get_passanger();

    Passes.add(n_pass.passport_number, n_pass);

    UserAddWindow->close();

    refreshPassTable();
}

void MainWindow::on_del_pass_but_clicked()
{
    if (ui->tab_pass->selectedItems().isEmpty())
        return;

    int row = ui->tab_pass->selectedItems().first()->row();
    //int col = ui->tab_pass->selectedItems().first()->column();

    Passes.removeByKey(ui->tab_pass->item(row, 0)->text().toStdString());

    refreshPassTable();
}

void MainWindow::on_del_all_pass_but_clicked()
{
    Passes.clear();
    refreshPassTable();
}

void MainWindow::on_line_pas_num_textChanged(const QString &arg1)
{
    FindPassanger(ui->line_pas_name->text(), arg1);
}

void MainWindow::on_line_pas_name_textChanged(const QString &arg1)
{
    FindPassanger(arg1, ui->line_pas_num->text());
}

void MainWindow::FindPassanger(QString name, QString num)
{
        Passanger* pass = Passes.getAll();
        int n = Passes.getSize();

        Passanger* f_pas = new Passanger[n];
        int f_size = 0;

        for (int i = 0; i < n; i++)
        {
            if (pass[i].full_name.find(name.toStdString()) != std::string::npos
                    && pass[i].passport_number.find(num.toStdString()) != std::string::npos)
                f_pas[f_size++] = pass[i];
        }

        refreshPassTable(f_pas, f_size);
        delete[] pass;
}

void MainWindow::on_tab_pass_itemDoubleClicked(QTableWidgetItem *item)
{
    if (PassWin == nullptr)
    {
        int row = item->row();
        std::string pas_num = ui->tab_pass->item(row, 0)->text().toStdString();

        Passanger curPas = Passes[pas_num];
        /*int t_size = 0;
        Ticket* pas_tickets = ticketsOfPass(pas_num, &t_size);*/

        PassWin = new PassForm(curPas, &Tickets,/*pas_tickets, t_size,*/ &Flights);
        PassWin->setAttribute(Qt::WA_DeleteOnClose);

        connect(PassWin, &PassForm::returnTicket, this, &MainWindow::returnTicket);
        connect(PassWin, &PassForm::destroyed, this, &MainWindow::destroyedPassWin);
        connect(PassWin, &PassForm::issueNewTicket, this, &MainWindow::issueNewTicket);
        connect(this, &MainWindow::refreshPassWin, PassWin, &PassForm::refreshTickets);

        PassWin->show();
    }
}

Ticket* MainWindow::ticketsOfPass(std::string pas_num, int* pas_size)
{
    Ticket* tickets = Tickets.getAll();
    int size_all = Tickets.size();
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
    return pas_tic;
}

void MainWindow::returnTicket(Ticket t)
{
    Ticket to_del = Tickets.findData(t);
    if (to_del.passport_number != "" && to_del.flight_number != "")
    {
        std::string fly_num = to_del.flight_number;
        Flights.get(Flight(to_del.flight_number)).free_seats++;
        Tickets.remove(t);

        /*int size_t = 0;
        Ticket* ticks = ticketsOfPass(PassWin->getCurPass().passport_number, &size_t);*/
        //PassWin->refreshTickets(/*ticks, size_t*/);
        refreshTickTable();


        Flight fly = Flights.get(Flight(fly_num));
        /*int t_size = 0;
        Ticket* flight_tickets = ticketsOfFlight(fly_num, &t_size);*/

        emit refreshFlyWin(/*fly, flight_tickets, t_size*/);
        emit refreshPassWin();
    }
}

void MainWindow::issueNewTicket(Flight f)
{
    Flight fly = Flights.get(f);
    if (fly.a_from != "" && fly.a_to != "" && fly.free_seats > 0)
    {
        Ticket nt = newTicket(PassWin->getCurPass(), fly);
        Flights.get(f).free_seats--;
        Tickets.push_back(nt);

        //PassWin->refreshTickets();
        refreshTickTable();
        emit refreshFlyWin(/*Flights.get(f)*/);
        emit refreshPassWin();
    }
}

Ticket MainWindow::newTicket(Passanger pas, Flight fly)
{
    srand(time(NULL));
    int n;
    std::string num;
    do {
        num.clear();
        for (int i = 0; i < 9; i++)
        {
            n = rand() % 10;
            num += std::to_string(n);
        }
    } while(Tickets.contains(Ticket(num)));

    return Ticket(pas.passport_number, fly.flight_number, num);
}



void MainWindow::on_add_flight_but_clicked()
{
    FlightAddWindow = new AddFlightForm();
    FlightAddWindow->setAttribute(Qt::WA_DeleteOnClose);

    connect(FlightAddWindow, SIGNAL(pressed_add()), this, SLOT(addFlight()));

    FlightAddWindow->show();
}

void MainWindow::addFlight()
{
    Flight n_fly = FlightAddWindow->getFly();

    Flights.add(n_fly);

    FlightAddWindow->close();

    refreshFlightTable();
}

void MainWindow::on_del_flight_but_clicked()
{
    if (ui->tab_flight->selectedItems().isEmpty())
        return;

    int row = ui->tab_flight->selectedItems().first()->row();
    int col = ui->tab_flight->selectedItems().first()->column();

    Flight tmp = Flight(ui->tab_flight->item(row, col)->text().toStdString());

    Flights.remove(tmp);

    int size_t = 0;
    Ticket* ticks = ticketsOfFlight(tmp.flight_number, &size_t);

    for (int i = 0; i < size_t; i++)
    {
        Tickets.remove(ticks[i]);
    }

    delete[] ticks;
    refreshFlightTable();
    refreshTickTable();
    emit refreshFlyWin();
    emit refreshPassWin();
}

void MainWindow::on_clear_flight_but_clicked()
{
    Flights.clear();
    Tickets.clear();
    refreshTickTable();
    refreshFlightTable();
}

//--------Finding flight----------
void MainWindow::on_line_a_to_textChanged(const QString &arg1)
{
    FindFlight(ui->line_num_air->text(), arg1);
}

void MainWindow::on_line_num_air_textChanged(const QString &arg1)
{
    FindFlight(arg1, ui->line_a_to->text());
}

void MainWindow::FindFlight(QString num, QString a_to)
{
    Flight* flys = Flights.getAll();
    int n = Flights.size();

    Flight* BMpas = new Flight[n];
    int f_size = 0;

    if (a_to.toStdString() != "")
    {
        for (int i = 0; i < n; i++)
        {
            if (flys[i].flight_number.find(num.toStdString()) != std::string::npos
                    && boyer_moore(flys[i].a_to, a_to.toStdString()))
                BMpas[f_size++] = flys[i];
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (flys[i].flight_number.find(num.toStdString()) != std::string::npos)
                BMpas[f_size++] = flys[i];
        }
    }

    refreshFlightTable(BMpas, f_size);
    delete[] flys;
}

bool MainWindow::boyer_moore(std::string a_to, std::string pat)
{
    int table[256];

    int size_a = a_to.size();
    int size_pat = pat.size();

    if (size_a >= size_pat)
    {
        for (int i = 0; i < 256; i++)
            table[i] = size_pat;

        for (int i = 0; i < size_pat; i++)
            table[(int) pat.at(i)] = i;

        int s = 0;
        while (s <= (size_a - size_pat))
        {
            int j = size_pat - 1;

            while (j >= 0 && (a_to.at(s + j) == pat.at(j)))
                j--;

            if (j < 0)
                return true;

            s += std::max(1, j - table[(int) a_to.at(s + j)]);
        }
    }
    return false;
}
//---------------------------------

void MainWindow::on_tab_flight_itemDoubleClicked(QTableWidgetItem *item)
{
    if (FlyWin == nullptr)
    {
        int row = item->row();
        std::string fly_num = ui->tab_flight->item(row, 0)->text().toStdString();

        Flight fly = Flights.get(Flight(fly_num));
        /*int t_size = 0;
        Ticket* flight_tickets = ticketsOfFlight(fly_num, &t_size);*/

        FlyWin = new FlightForm(fly, &Flights, &Tickets,/*flight_tickets, t_size,*/ &Passes);
        FlyWin->setAttribute(Qt::WA_DeleteOnClose);

        connect(this, &MainWindow::refreshFlyWin, this->FlyWin, &FlightForm::refreshTickets);
        connect(FlyWin, &FlightForm::destroyed, this, &MainWindow::destroyedFlyWin);

        FlyWin->show();
    }
}

Ticket* MainWindow::ticketsOfFlight(std::string fly_num, int* size)
{
    Ticket* tickets = Tickets.getAll();
    int size_all = Tickets.size();
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
    return pas_tic;
}

void MainWindow::destroyedFlyWin()
{
    this->FlyWin = nullptr;
}

void MainWindow::destroyedPassWin()
{
    this->PassWin = nullptr;
}
