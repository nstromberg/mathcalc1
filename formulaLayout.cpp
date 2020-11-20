#include "formulaLayout.h"
#include "ui_formulaLayout.h"

FormulaLayout::FormulaLayout(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::formulaLayout_UI)
{
    ui->setupUi(this);
}

FormulaLayout::~FormulaLayout()
{
    delete ui;
}
