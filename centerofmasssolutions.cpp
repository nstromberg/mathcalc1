#include "centerofmasssolutions.h"
#include "ui_centerOfMassSolutions.h"

centerofmasssolutions::centerofmasssolutions(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::centerOfMassSolutions_UI)
{
    ui->setupUi(this);
}

centerofmasssolutions::~centerofmasssolutions()
{
    delete ui;
}
