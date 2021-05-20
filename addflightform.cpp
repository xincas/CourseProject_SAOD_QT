#include "addflightform.h"
#include "ui_addflightform.h"

AddFlightForm::AddFlightForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFlightForm)
{
    ui->setupUi(this);

    ui->dateEdit->setMinimumDateTime(QDateTime::currentDateTime());
}

AddFlightForm::~AddFlightForm()
{
    delete ui;
}

void AddFlightForm::on_add_but_clicked()
{
    fly = Flight(ui->line_num->text().toStdString(),
                 ui->line_name->text().toStdString(),
                 ui->line_from->text().toStdString(),
                 ui->line_to->text().toStdString(),
                 ui->dateEdit->date().toString("dd.MM.yyyy").toStdString(),
                 ui->timeEdit->time().toString("hh:mm").toStdString(),
                 ui->line_all_seats->text().toUInt(),
                 ui->line_free_seats->text().toUInt());

    if (fly.flight_number.size() < 7 || fly.a_from.size() < 4
            || fly.a_to.size() < 4 || fly.airline_name.size() < 4
            || fly.all_seats == 0 || fly.free_seats == 0)
        QMessageBox::warning(this, "Ошибка", "Не все поля заполнены!");
    else if (fly.free_seats > fly.all_seats)
        QMessageBox::warning(this, "Ошибка", "Свободных мест больше общего числа!");
    else
        emit pressed_add();
}

Flight AddFlightForm::getFly()
{
    return fly;
}

void AddFlightForm::on_cancel_but_clicked()
{
    this->close();
}

bool AddFlightForm::checkFills()
{
    QString str = "Incorrect data:";

    if (fly.free_seats > fly.all_seats || fly.free_seats < 0 || fly.all_seats < 0)
        str += "\nFree and all seats";

    return false;
}
