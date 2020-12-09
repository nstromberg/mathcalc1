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


/** commented code will allow user to select a formula


#include "formulaLayout.h"
#include "ui_formulaLayout.h"

FormulaLayout::FormulaLayout(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::formulaLayout_UI)

{
    ui->setupUi(this);


    ui->FormulaComboBox->addItem("Select");
    //QVector<QString> formulas;

    formulas << "Minimum Speed";

    for(int i = 0; i < formulas.size(); i++) {
        ui->FormulaComboBox->addItem(formulas[i]);
    }
}

FormulaLayout::~FormulaLayout()
{
    delete ui;
}


void FormulaLayout::Initializer()
{

}


void FormulaLayout::on_FormulaComboBox_currentIndexChanged(const QString &formula){

    if (formula != QString("Select"))
    {
        if(formula == "Minimum Speed"){
            minimumSpeed = new MinimumSpeed;
            minimumSpeed->ShowMinSpeed();
        }
    }
}




*/
