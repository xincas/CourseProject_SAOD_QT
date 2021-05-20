#ifndef ADDFLIGHTFORM_H
#define ADDFLIGHTFORM_H

#include <QWidget>
#include <QMessageBox>
#include "MyStructs.h"

namespace Ui {
class AddFlightForm;
}

class AddFlightForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddFlightForm(QWidget *parent = nullptr);
    ~AddFlightForm();
    Flight getFly();


signals:
    void pressed_add();

private slots:
    void on_add_but_clicked();
    void on_cancel_but_clicked();
    bool checkFills();

private:
    Ui::AddFlightForm *ui;
    Flight fly;
};

#endif // ADDFLIGHTFORM_H
