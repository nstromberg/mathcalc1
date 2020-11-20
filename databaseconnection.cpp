#include "databaseconnection.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

//Constructor
DatabaseConnection::DatabaseConnection(){

}

//Establishes basic connection with the AWS database. Returns a 0 or -1 based on connection status.
int DatabaseConnection::establish_database_connection(){

    //Attempts to open a connection to the database and returns connection status accordingly.
    db.setHostName(DBAddr);
    db.setUserName(DBUser);
    db.setDatabaseName(DBName);
    db.setPassword(DBPass);
    if(db.open()){
        qDebug() << "Connection Status: Connected";
        return 0;
    }else{
        qDebug() << "Connection Status: Not Connected";
        qDebug() << db.lastError();
        return -1;
    }
}

//Executes and returns data for any given Query. If data is present a vector of the returned contents will be returned.
std::vector<std::vector<QString>> DatabaseConnection::fetch_data_from_server(QString query_string){

    //Executes the SQL query and stores it.
    QSqlQuery query;
    query.exec(query_string);

    //2D vector initialization to store the query results. Outer vector: list of rows, Inner vector: list of column values for a single row.
    std::vector<std::vector<QString>> query_results;

    //Loops through all the query results.
    while (query.next()) {
        QSqlRecord row = query.record();

        //Vector initialization for fetching a specific row of the query results.
        std::vector<QString> single_row;

        //For every column in the query result, add individual values to a vector.
        for(int i=0; i < row.count(); i++){
            QString row_value = row.value(i).toString();
            single_row.push_back(row_value);
        }
        query_results.push_back(single_row);
    }
    return query_results;
}


