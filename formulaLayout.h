#ifndef FORMULALAYOUT_H
#define FORMULALAYOUT_H

#include <QWidget>
#include <ui_formulaLayout.h>
QT_BEGIN_NAMESPACE
namespace Ui { class FormulaLayout; }
QT_END_NAMESPACE

class FormulaLayout : public QWidget
{
    Q_OBJECT

public:
    FormulaLayout(QWidget *parent = nullptr);
    ~FormulaLayout();

private:
    Ui::formulaLayout_UI *ui;
};
#endif // FORMULALAYOUT_H


/** commented code allows user to select a formula

#ifndef FORMULALAYOUT_H
#define FORMULALAYOUT_H
#include "minimumSpeed.h"

#include <QWidget>
#include <ui_formulaLayout.h>
QT_BEGIN_NAMESPACE
namespace Ui { class FormulaLayout; }
QT_END_NAMESPACE

class FormulaLayout : public QWidget
{
    Q_OBJECT

public:
    FormulaLayout(QWidget *parent = nullptr);
    ~FormulaLayout();


private:
    Ui::formulaLayout_UI *ui;
    MinimumSpeed * minimumSpeed;
    QVector<QString> formulas;
    void Initializer();


private slots:
    void on_FormulaComboBox_currentIndexChanged(const QString &formula);
};
#endif // FORMULALAYOUT_H



*/
