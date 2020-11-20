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
