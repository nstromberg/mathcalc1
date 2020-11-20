#ifndef UNITTESTS_H
#define UNITTESTS_H
#include "formulas.h"
#include <QObject>
#include <QWidget>

class unitTests : public QWidget
{
    Q_OBJECT
public:
    unitTests(QWidget *parent = nullptr, int numTests = 0, int passedTests = 0);
    int runAll();
    int calculateFormulas();
    void testWeightDistributions();
    void testComLong();
    void testCalculateComHt();
    void displayResults(QVector<float> testCalcResults, QVector<float> programResults, QVector<QString> variables);
    void testCalculateMinimumSpeed();
    void testCalculateVelocity();

private:
    QString curbWeight;
    QString inputWeightDist;
    QString frontAxleWeight;
    QString wheelBase;
    QString inputOverallWeight;
    QString heightCenterFrontWheels;
    QString heightCenterRearWheelsRaised;
    QString weightFrontWheelsRearRaised;
    int numTests;
    int passedTests;

private:
    Formulas formulas;
};



#endif // UNITTESTS_H
