#ifndef VEHICLELOOKUP_H
#define VEHICLELOOKUP_H

#include <QWidget>
#include <ui_VehicleLookUp.h>
#include "databaseconnection.h"
QT_BEGIN_NAMESPACE
namespace Ui { class VehicleLookUp; }
QT_END_NAMESPACE

class VehicleLookUp : public QWidget
{
    Q_OBJECT

public:
    VehicleLookUp(QWidget *parent = nullptr);
    ~VehicleLookUp();

private slots:
    void on_YearComboBox_currentIndexChanged(const QString &arg1);

    void on_SelectAMakeComboBox_currentIndexChanged(const QString &arg1);

    void on_SelectAModelComboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();
    
    void on_CVS_YearComboBox_currentIndexChanged(const QString &arg1);

    void on_CVS_MakeComboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_2_clicked();

private:
    Ui::VehicleLookUp_UI *ui;
    DatabaseConnection *db;

};
#endif // VEHICLELOOKUP_H
