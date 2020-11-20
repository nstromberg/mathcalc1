#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QtSql>
#include <QSqlDatabase>
#include <QString>
#include <vector>

class DatabaseConnection
{
public:
    DatabaseConnection();

    int establish_database_connection();
    std::vector<std::vector<QString>> fetch_data_from_server(QString query);
    int load_data_to_server(QString query);

private:
    const QString DBAddr = "deltav-devtest.ci5dqgpsfw9c.us-east-2.rds.amazonaws.com";
    const QString DBName = "DeltaV_Test_Database_1";
    const QString DBUser = "DeltaV499s18";
    const QString DBPass = "CS499UK!";

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

};

#endif // DATABASECONNECTION_H
