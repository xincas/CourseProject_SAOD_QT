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
                         ui->dateEdit->date().toString("dd.MM.yyyy").toStdString(),
                         ui->line_issplace->text().toStdString());

    if (pass.full_name.size() < 5 || pass.passport_number.size() < 11 || pass.issue_date.size() < 5)
        QMessageBox::warning(this, "Ошибка", "Не все поля заполнены!");
    else
        emit pressed_add();
}

Passanger UserAddForm::get_passanger()
{
    return pass;
}
