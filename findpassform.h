#ifndef FINDPASSFORM_H
#define FINDPASSFORM_H

#include <QWidget>

namespace Ui {
class FindPassForm;
}

class FindPassForm : public QWidget
{
    Q_OBJECT

public:
    explicit FindPassForm(QWidget *parent = nullptr);
    ~FindPassForm();

private:
    Ui::FindPassForm *ui;
};

#endif // FINDPASSFORM_H
