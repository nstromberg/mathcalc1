#include "unittests.h"
#include "formulas.h"
#include <QDebug>

unitTests::unitTests(QWidget *parent, int numTests, int passedTests, float epsilon)
    : QWidget(parent)
    , numTests(numTests)
    , passedTests(passedTests)
    , epsilon(epsilon)
{

}

/**
 * The method displays the results from the tests, and whether or not the test passed
 * @param {QVector} testCalcResults
 * @param {QVector} programResults
 * @param {QVector} variables
 */
void unitTests::displayResults(QVector<float> testCalcResults, QVector<float> programResults, QVector<QString> variables)
{

    for(int i = 0; i < testCalcResults.size(); i++){
        if(fabs(testCalcResults[i] - programResults[i]) <= epsilon){
            passedTests++;
            numTests++;
            qDebug() << variables[i] << "\t" << testCalcResults[i] << "\t"  <<  programResults[i] << "\tTrue";

        }
        else{
            numTests++;
            qDebug() << variables[i] << "\t" << testCalcResults[i] << "\t" << programResults[i] << "\tFalse";
        }
    }

    qDebug() << "=================================================================";
}

/**
 * The method tests the calculation for the weight distributions
 */
void unitTests::testWeightDistributions()
{
    QVector<QString> testVals;
    QVector<QString> variables;

    variables << "overall weight:  " << "front axle weight:  " << "rear axel weight:  "
              << "front left weight:" << "front right weight:" << "rear left weight:"
              << "rear right weight:" ;

    //determines when to start testing the calculation based on the number of test vals that have been iterated through
    int index = 0;
    //hard coded values for testing
    testVals << "40/60" << "4000";

    for(int i = 0; i < testVals.length(); i++){
        QVector<float> testCalcResults;
        QVector<float> programResults;
        index++;

        if(index % 2 == 0){

            //stores the hard coded values
            float hardCodeCurbWeight, hardCodeFrontDist, hardCodeRearDist;
            //stores the test calculation results
            float testFrontAxleWeight, testRearAxleWeight, testFrontTireWeight, testRearTireWeight, testOverallWeight;

            //set values and perform program's calculation
            formulas.SETweightDistributionLE(testVals[i-1]);
            formulas.SETcurbWeightLE(testVals[i]);
            formulas.calculateWeightDistributions();
            //append results from program's calculation
            programResults.append(formulas.GEToverallWeightLEval());
            programResults.append(formulas.GETfrontAxleWeightLEval());
            programResults.append(formulas.GETrearAxleWeightLEval());
            programResults.append(formulas.GETfrontLeftWeightLEval());
            programResults.append(formulas.GETfrontRightWeightLEval());
            programResults.append(formulas.GETrearLeftWeightLEval());
            programResults.append(formulas.GETrearRightWeightLEval());

            //hard coded values for the test calculation
            hardCodeCurbWeight = testVals[i].toFloat();
            hardCodeFrontDist = testVals[i-1].split("/")[0].toFloat();
            hardCodeRearDist = testVals[i-1].split("/")[1].toFloat();

            qDebug() << "TEST " << index/2 << ":";
            qDebug() << "Curb Weight:\t" << hardCodeCurbWeight;
            qDebug() << "Front Distribution:\t" << hardCodeFrontDist;
            qDebug() << "Rear Distribution:\t" << hardCodeRearDist;
            qDebug() << "---------------------------------------------------------";
            qDebug() << "Variable\t\t\tExpected\tReceived\tPassed";
            qDebug() << "---------------------------------------------------------";

            //test calculation
            testOverallWeight = hardCodeCurbWeight;

            testFrontAxleWeight = hardCodeCurbWeight * (hardCodeFrontDist/100.0);
            testFrontAxleWeight = formulas.roundPt5(testFrontAxleWeight);

            testRearAxleWeight = hardCodeCurbWeight * (hardCodeRearDist/100.0);
            testRearAxleWeight = formulas.roundPt5(testRearAxleWeight);

            testFrontTireWeight = testFrontAxleWeight/2;
            testFrontTireWeight = formulas.roundPt5(testFrontTireWeight);

            testRearTireWeight = testRearAxleWeight/2;
            testRearTireWeight = formulas.roundPt5(testRearTireWeight);
            //append results from test's calculation
            testCalcResults.append(testOverallWeight);
            testCalcResults.append(testFrontAxleWeight);
            testCalcResults.append(testRearAxleWeight);
            testCalcResults.append(testFrontTireWeight);
            testCalcResults.append(testFrontTireWeight);
            testCalcResults.append(testRearTireWeight);
            testCalcResults.append(testRearTireWeight);

            //display to the user the results from the tests
            displayResults(testCalcResults, programResults, variables);
        }
    }//end for loop
}

/**
 * The method tests the calculation for the horrizontal center of mass
 */
void unitTests::testComLong()
{
    QVector<QString> testVals;
    QVector<QString> variables;
    variables << "Com Long:  ";

    //determines when to start testing the calculation based on the number of test vals that have been iterated through
    int index = 0;
    //hard coded values for testing
    testVals << "1600" << "200" << "4000";

    for(int i = 0; i < testVals.length(); i++){
        QVector<float> testCalcResults;
        QVector<float> programResults;
        index++;

        if(index % 3 == 0){
            //stores the hard coded values
            float hardCodeFrontAxleWeight, hardCodeWheelBase, hardCodeOverallWeight;
            //stores the test calculation results
            float testCOMLong;
            //set values and perform program's calculation
            formulas.SETfrontAxleWeightLE(testVals[i-2]);
            formulas.SETwheelBaseLE(testVals[i-1]);
            formulas.SEToverallWeightLE(testVals[i]);
            formulas.calculateComLong();

            //append results from program's calculation
            programResults.append(formulas.GETcomLongSolutionsLEval());

            //hard coded values for the test calculation
            hardCodeFrontAxleWeight = testVals[i-2].toFloat();
            hardCodeWheelBase = testVals[i-1].toFloat();
            hardCodeOverallWeight = testVals[i].toFloat();

            qDebug() << "TEST " << index/3 << ":";
            qDebug() << "Front Axle Weight:\t" << hardCodeFrontAxleWeight;
            qDebug() << "Wheel Base:\t" << hardCodeWheelBase;
            qDebug() << "Overall Weight:\t" << hardCodeOverallWeight;
            qDebug() << "---------------------------------------------------------";
            qDebug() << "Variable\t\tExpected\tReceived\tPassed";
            qDebug() << "---------------------------------------------------------";

            //test calculation
            testCOMLong = (hardCodeFrontAxleWeight * hardCodeWheelBase) / hardCodeOverallWeight;
            testCOMLong = formulas.roundPt5(testCOMLong);
            //append results from test's calculation
            testCalcResults.append(testCOMLong);
            //display to the user the results from the tests
            displayResults(testCalcResults, programResults, variables);
        }

    }//end for loop
}

/**
 * The method tests the calculation for the center of mass height
 */
void unitTests::testCalculateComHt()
{
    QVector<QString> testVals;
    QVector<QString> variables;

    //determines when to start testing the calculation based on the number of test vals that have been iterated through
    int index = 0;
    //stores the hard coded values
    float hardCodeOverallWeight, hardCodeFrontAxleWeight, hardCodeWheelBase, hardCodeHeightCenterFrontWheels, hardCodeHeightCenterRearWheelsRaised, hardCodeWeightFrontWheelsRearRaised;
    //stores the test calculation results
    float testComHt, testWeightDiff, testHeightDiff;

    QString testComHtStringVersion;

    variables << "Com Ht ";

    testVals << "4000" << "1600" << "200" << "12" << "123" << "123"
              << "400022" << "160023" << "2003" << "122" << "12233" << "12233";

    for(int i = 0; i < testVals.length(); i++) {
        QVector<float> testCalcResults;
        QVector<float> programResults;
        index++;

        if(index % 6 == 0){

            //set values and perform program's calculation
            formulas.SEToverallWeightLE(testVals[i-5]);
            formulas.SETfrontAxleWeightLE(testVals[i-4]);
            formulas.SETwheelBaseLE(testVals[i-3]);
            formulas.SETheightCenterFrontWheelsLE(testVals[i-2]);
            formulas.SETheightCenterRearWheelsRaisedLE(testVals[i-1]);
            formulas.SETweightFrontWheelsRearRaisedLE(testVals[i]);
            formulas.calculateComHt();
            //append results from program's calculation
            programResults.append(formulas.GETcomHtSolutionsLEval());

            //hard coded values for the test calculation
            hardCodeOverallWeight = testVals[i-5].toFloat();
            hardCodeFrontAxleWeight = testVals[i-4].toFloat();
            hardCodeWheelBase = testVals[i-3].toFloat();
            hardCodeHeightCenterFrontWheels = testVals[i-2].toFloat();
            hardCodeHeightCenterRearWheelsRaised = testVals[i-1].toFloat();
            hardCodeWeightFrontWheelsRearRaised = testVals[i].toFloat();

            qDebug() << "TEST " << index/6 << ":";
            qDebug() << "Overall Weight:\t\t\t" << hardCodeOverallWeight;
            qDebug() << "Front Axle Weight:\t\t\t" << hardCodeFrontAxleWeight;
            qDebug() << "Wheel Base:\t\t\t" << hardCodeWheelBase;
            qDebug() << "Height Center Front Wheels:\t\t" <<hardCodeHeightCenterFrontWheels;
            qDebug() << "Height Center Rear Wheels raised:\t" << hardCodeHeightCenterRearWheelsRaised;
            qDebug() << "Weight Center Front Wheels rear raised:\t" <<hardCodeWeightFrontWheelsRearRaised;
            qDebug() << "---------------------------------------------------------";
            qDebug() << "Variable\t\tExpected\tReceived\tPassed";
            qDebug() << "---------------------------------------------------------";

            //test calculation
            testWeightDiff = hardCodeWeightFrontWheelsRearRaised - hardCodeFrontAxleWeight;
            testHeightDiff = hardCodeHeightCenterRearWheelsRaised - hardCodeHeightCenterFrontWheels;

            testComHt = hardCodeHeightCenterFrontWheels + ((testWeightDiff * hardCodeWheelBase * qSqrt((hardCodeWheelBase * hardCodeWheelBase) - (testHeightDiff * testHeightDiff))) / (hardCodeOverallWeight * testHeightDiff));
            testComHt = formulas.roundPt5(testComHt);

            testComHtStringVersion.setNum(testComHt);
            testComHt = testComHtStringVersion.toFloat();
            //append results from test's calculation
            testCalcResults.append(testComHt);

            //display to the user the results from the tests
            displayResults(testCalcResults, programResults, variables);
        }
    }//end for loop
}

/**
 * This method tests the calculation for the minimum speed
 */
void unitTests::testCalculateMinimumSpeed()
{
    QVector<QString> testVals1;
    QVector<QString> variables;

    variables << "minimumSpeed";
    //determines when to start testing the calculation based on the number of test vals that have been iterated through
    int index = 0;
    //values in groups of two: first is acceleration drag, and the second is skid distance
    testVals1 << "2" << "100"
              << "1" << "30"
              << "3" << "2622133478"
              << "0.3" << "0.5";

    //stores the hard coded values
    float hardCodeSkidDistance, hardCodeAccelDrag;
    //stores the test calculation results
    float testMinSpeed;
    //used to handle large numbers
    QString testMinSpeedStringVersion;

    for(int i = 0; i < testVals1.length(); i++){
        QVector<float> testCalcResults;
        QVector<float> programResults;
        index++;
        if(index % 2 == 0){

            //set values and perform program's calculation
            formulas.SETskidDistanceLE(testVals1[i]);
            formulas.SETAccelDragLE(testVals1[i - 1]);
            formulas.calculateMinimumSpeed();
            //append results from program's calculation
            programResults.append(formulas.GETminimumSpeedLEval());
            //hard coded values for the test calculation
            hardCodeSkidDistance = testVals1[i].toFloat();
            hardCodeAccelDrag = testVals1[i-1].toFloat();

            qDebug() << "TEST " << index/2 << ":";
            qDebug() << "Skid Distance:\t" << hardCodeSkidDistance;
            qDebug() << "Acceleration Drag:\t" << hardCodeAccelDrag;
            qDebug() << "-------------------------------------------------";
            qDebug() << "Variable\t\tExpected\tReceived\tPassed";
            qDebug() << "-------------------------------------------------";
            //test calculation
            testMinSpeed = qSqrt(30 * hardCodeSkidDistance * hardCodeAccelDrag);
            testMinSpeed = formulas.round2Places(testMinSpeed);

            testMinSpeedStringVersion.setNum(testMinSpeed);

            testMinSpeed = testMinSpeedStringVersion.toFloat();

            //append results from test's calculation
            testCalcResults.append(testMinSpeed);

            //display to the user the results from the tests
            displayResults(testCalcResults, programResults, variables);
        }
    }//end for loop
}

/**
 * This method tests the calculation for velocity
 */
void unitTests::testCalculateVelocity()
{
    QVector<QString> testVals;
    QVector<QString> variables;

    variables << "velocity";

    //used to convert minimum speed to velocity
    float const conversionVar = 1.466;
    //stores the hard coded values
    float hardCodeMinSpeed;
    //stores the test calculation results
    float testVelocity;
    QString testVelocityStringVersion;
    //determines when to start testing the calculation based on the number of test vals that have been iterated through
    int index = 0;

    //each test value is minimum speed
    testVals << "100" << "2" << "30" << "0.5" << "2001" << "23342232423";

    for(int i = 0; i < testVals.length(); i++){
        QVector<float> testCalcResults;
        QVector<float> programResults;
        index++;

        if(index % 1 == 0){

            //set values and perform program's calculation
            formulas.SETminimumSpeedLE(testVals[i]);
            formulas.calculateVelocity();
            //append results from program's calculation
            programResults.append(formulas.GETvelocityLEval());
            //hard coded values for the test calculation
            hardCodeMinSpeed = testVals[i].toFloat();

            qDebug() << "TEST " << index << ":";
            qDebug() << "Minimum speed:\t" << hardCodeMinSpeed;
            qDebug() << "-------------------------------------------------";
            qDebug() << "Variable\t\tExpected\tReceived\tPassed";
            qDebug() << "-------------------------------------------------";

            //test calculation
            testVelocity = conversionVar * hardCodeMinSpeed;
            testVelocity = formulas.round2Places(testVelocity);

            //conversion used for large numbers
            testVelocityStringVersion.setNum(testVelocity);
            testVelocity = testVelocityStringVersion.toFloat();

            //append results from test's calculation
            testCalcResults.append(testVelocity);

            //display to the user the results from the tests
            displayResults(testCalcResults, programResults, variables);

        }

    }//end for loop

}

/**
 * Tests the formula calculations. Returns 0 if any test fails. Returns 1 if all test are successful
 * @return {Number} a value that indicates if all or some/none of the tests have passed
 */
int unitTests::calculateFormulas()
{
    qDebug() << "****************************************************";

    qDebug() << "********** TEST WEIGHT DISTRIBUTIONS ***************";
    testWeightDistributions();
    qDebug() << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";

    qDebug() << "********** TEST COM LONG ***************************";
    testComLong();
    qDebug() << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| ";

    qDebug() << "********** TEST COM HT *****************************";
    testCalculateComHt();
    qDebug() << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| ";

    qDebug() << "********** TEST Minimum Speed **********************";
    testCalculateMinimumSpeed();
    qDebug() << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| ";

    qDebug() << "********** TEST Velocity **********************";
    testCalculateVelocity();
    qDebug() << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| ";

    qDebug() << "Number of Passed Tests: " << passedTests << " / " << numTests;
    //if all tests pass, return 1 (or true) to indicate the tests passed
    if(passedTests == numTests) {
        return 1;
    }
    //return 0 if some or all tests do not pass
    return 0;
}

/**
 * Runs all tests. Returns 0 if failed. Returns 1 if successful
 * @return {Number} a value that indicates if all or some/none of the tests have passed
 */
int unitTests::runAll()
{

    if (!calculateFormulas())
    {
        qDebug() << "calculateFormulas failed";
        return 0;
    }

    return 1;
}
