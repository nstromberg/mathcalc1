#include "formulas.h"
#include "unittests.h"
#include <QtDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    /**
     * NOTE:
     *      To run the unit tests, change the value of the boolean variable (test) to 1
     *      To run application, change the value of the boolean variable (test) to 0
     */
    bool test = 0;
    QApplication a(argc, argv);

    if (!test)
    {
        //for running the application
        Formulas w;
        w.show();
        return a.exec();
    }
    else
    {
        //For testing
        unitTests test;
        if (test.runAll())
        {
            qDebug() << "Tests successful";
        }
        else
        {
            qDebug() << "Tests failed";
        }
        return 0;
    }
}
