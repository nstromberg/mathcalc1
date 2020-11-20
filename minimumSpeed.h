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
