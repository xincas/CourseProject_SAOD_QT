#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMessageBox>
#include "MyStructs.h"
#include "useraddform.h"
#include "passform.h"
#include "addflightform.h"
#include "flightform.h"
#include "ctime"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addPassanger();
    void addFlight();

    void returnTicket(Ticket t);
    void issueNewTicket(Flight f);
    Ticket newTicket(Passanger pas, Flight fly);

    void on_add_pass_but_clicked();
    void on_del_pass_but_clicked();
    void on_del_all_pass_but_clicked();
    void on_line_pas_num_textChanged(const QString &arg1);
    void on_line_pas_name_textChanged(const QString &arg1);
    void on_tab_pass_itemDoubleClicked(QTableWidgetItem *item);

    void on_add_flight_but_clicked();
    void on_del_flight_but_clicked();
    void on_clear_flight_but_clicked();
    void on_line_a_to_textChanged(const QString &arg1);
    void on_line_num_air_textChanged(const QString &arg1);
    void on_tab_flight_itemDoubleClicked(QTableWidgetItem *item);

    void destroyedFlyWin();
    void destroyedPassWin();

private:
    Ui::MainWindow *ui;

signals:
    void refreshFlyWin(/*Flight fly, Ticket* tickets, int n_t*/);
    void refreshPassWin();

private:
    HashTable<std::string, Passanger> Passes;
    List<Ticket> Tickets;
    AVL<Flight> Flights;
    UserAddForm* UserAddWindow = nullptr;
    AddFlightForm* FlightAddWindow = nullptr;
    PassForm* PassWin = nullptr;
    FlightForm* FlyWin = nullptr;

private:
    void createPassengersTable();
    void createTicketsTable();
    void createFlightsTable();

    void refreshPassTable(Passanger* passes = nullptr, int p_size = 0);
    void refreshTickTable(Ticket* f_tick = nullptr, int t_size = 0);
    void refreshFlightTable(Flight* f_flights = nullptr, int f_size = 0);

    void FindPassanger(QString name, QString num);
    Ticket* ticketsOfPass(std::string pas_num, int* pas_size);

    void FindFlight(QString num, QString a_to);
    bool boyer_moore(std::string a_to, std::string pat);
    Ticket* ticketsOfFlight(std::string fly_num, int* size);

};
#endif // MAINWINDOW_H
