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
