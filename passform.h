#ifndef PASSFORM_H
#define PASSFORM_H

#include <QWidget>
#include "MyStructs.h"

namespace Ui {
class PassForm;
}

class PassForm : public QWidget
{
    Q_OBJECT

public:
    explicit PassForm(Passanger curPas,
                      List<Ticket>* ticks,
                      AVL<Flight>* flight,
                      HashTable<std::string, Passanger>* passes,
                      QWidget *parent = nullptr);
    ~PassForm();
    Passanger getCurPass();

public slots:
    void refreshTables();

private slots:
    void on_issue_ticket_but_clicked();
    void on_return_ticket_but_clicked();

signals:
    void returnTicket(Ticket t);
    void issueNewTicket(Flight f);

private:
    Passanger pas_;
    List<Ticket>* ticks;
    AVL<Flight> *fligths;
    HashTable<std::string, Passanger>* passes;

private:
    Ui::PassForm *ui;

private:
    void createTableTickets();
    void refreshTableTickets();
    void createTablePurchase();
    void refreshTablePurchase();
    void fillForms();

    Ticket* ticketsOfPass(std::string pas_num, int* pas_size);
};

#endif // PASSFORM_H
