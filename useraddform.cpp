#include "useraddform.h"
#include "ui_useraddform.h"

UserAddForm::UserAddForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserAddForm)
{
    ui->setupUi(this);
}

UserAddForm::~UserAddForm()
{
    delete ui;
}

void UserAddForm::on_cancel_but_clicked()
{
    this->close();
}

void UserAddForm::on_add_but_clicked()
{
    pass = Passanger(ui->line_pass_num->text().toStdString(),
                         ui->line_name->text().toStdString(),
                         ui->line_b_date->text().toStdString(),
                         ui->line_issplace->text().toStdString());

    emit pressed_add();
}

Passanger UserAddForm::get_passanger()
{
    return pass;
}
