#include "findpassform.h"
#include "ui_findpassform.h"

FindPassForm::FindPassForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindPassForm)
{
    ui->setupUi(this);
}

FindPassForm::~FindPassForm()
{
    delete ui;
}
