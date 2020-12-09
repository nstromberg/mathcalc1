#ifndef MINIMUMSPEED_H
#define MINIMUMSPEED_H

#include <QWidget>
#include <ui_minimumSpeed.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MinimumSpeed; }
QT_END_NAMESPACE

class MinimumSpeed : public QWidget
{
    Q_OBJECT

public:
    MinimumSpeed(QWidget *parent = nullptr);
    ~MinimumSpeed();

private:
    Ui::minimumSpeed_UI *ui;
};
#endif // MINIMUMSPEED_H


/** this code will allow you to open a new window for the min speed when the user selects the formula

#ifndef MINIMUMSPEED_H
#define MINIMUMSPEED_H

#include <QWidget>
#include <ui_minimumSpeed.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MinimumSpeed; }
QT_END_NAMESPACE

class MinimumSpeed : public QWidget
{
    Q_OBJECT

public:
    MinimumSpeed(QWidget *parent = nullptr);
    ~MinimumSpeed();
    void ShowMinSpeed();
    void HideMinSpeed();
    void captureAccelVal();

private:
    Ui::minimumSpeed_UI *ui;
private slots:
    void on_AccelDragFLineEdit_textChanged();



friend class FormulaLayout;
};
#endif // MINIMUMSPEED_H



*/
