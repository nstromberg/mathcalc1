#ifndef CENTEROFMASSSOLUTIONS_H
#define CENTEROFMASSSOLUTIONS_H

#include <QWidget>
#include <ui_centerofmasssolutions.h>
QT_BEGIN_NAMESPACE
namespace Ui { class centerofmasssolutions; }
QT_END_NAMESPACE

class centerofmasssolutions : public QWidget
{
    Q_OBJECT

public:
    centerofmasssolutions(QWidget *parent = nullptr);
    ~centerofmasssolutions();

private:
    Ui::centerOfMassSolutions_UI *ui;
};
#endif // CENTEROFMASSSOLUTIONS_H
