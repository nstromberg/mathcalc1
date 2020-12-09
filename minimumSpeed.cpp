#include "minimumSpeed.h"
#include "ui_minimumSpeed.h"

MinimumSpeed::MinimumSpeed(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::minimumSpeed_UI)
{
    ui->setupUi(this);
}

MinimumSpeed::~MinimumSpeed()
{
    delete ui;
}


/** commented code allows user to open new window when min speed is selected
//NOTE: CODE DOES NOT WORK PROPERLY, BUT THIS WILL HELP YOU OPEN A NEW WINDOW WHEN A FORMULA IS SELECTED

#include "minimumSpeed.h"
#include "ui_minimumSpeed.h"
#include <QDebug>
MinimumSpeed::MinimumSpeed(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::minimumSpeed_UI)
{
    ui->setupUi(this);
    this->hide();
}

MinimumSpeed::~MinimumSpeed()
{
    delete ui;
}


void MinimumSpeed::ShowMinSpeed()
{
    this->show();
}

void MinimumSpeed::HideMinSpeed() {
    this->hide();
}
//captures values typed for the acceleration drag coefficient
void MinimumSpeed::captureAccelVal() {
    QLineEdit* ran =  ui->AccelDragFLineEdit;
    qDebug() << ran->text();
}

void MinimumSpeed::on_AccelDragFLineEdit_textChanged()
{
    captureAccelVal();
}




*/
