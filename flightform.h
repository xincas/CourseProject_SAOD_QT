#ifndef FLIGHTFORM_H
#define FLIGHTFORM_H

#include <QWidget>
#include <MyStructs.h>

namespace Ui {
class FlightForm;
}

class FlightForm : public QWidget
{
    Q_OBJECT

public:
    explicit FlightForm(Flight curFly,
                        AVL<Flight>* flys,
                        List<Ticket>* ticks,
                        HashTable<std::string, Passanger>* passes,
                        QWidget *parent = nullptr);
    ~FlightForm();

public slots:
    void refreshTickets();

signals:


private:
    Flight fly_;
    AVL<Flight>* flys;
    List<Ticket>* ticks;
    HashTable<std::string, Passanger> *passes_;

private:
    Ui::FlightForm *ui;

private:
    void createTable();
    void refreshTable();
    void fillForms();

    Ticket* ticketsOfFlight(std::string fly_num, int* size);
};

#endif // FLIGHTFORM_H
