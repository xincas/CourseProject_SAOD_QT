#ifndef USERADDFORM_H
#define USERADDFORM_H

#include <QWidget>
#include "MyStructs.h"

namespace Ui {
class UserAddForm;
}

class UserAddForm : public QWidget
{
    Q_OBJECT

public:
    explicit UserAddForm(QWidget *parent = nullptr);
    ~UserAddForm();
    Passanger get_passanger();

private slots:
    void on_cancel_but_clicked();
    void on_add_but_clicked();

signals:
    void pressed_add();

private:
    Ui::UserAddForm *ui;
    Passanger pass;
};

#endif // USERADDFORM_H
