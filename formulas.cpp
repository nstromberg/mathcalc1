
#include "formulas.h"

#include "ui_formulas.h"
#include <QDebug>
#include <QFileDialog>
#include <QPrinter>

Formulas::Formulas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Formulas_UI)
{
    ui->setupUi(this);
}

Formulas::~Formulas()
{
    delete ui;
}

float Formulas::roundPt5(float input)
{
    //Move decimal point over two places and get value of new ones and tens position
    int round = abs(int(input * 100) % 100);
    if (round < 25)
    {
        //Round down (truncate)
        input = int(input);
    }
    else if (round >= 75)
    {
        if (input < 0)
        {
            //Round up (truncate and sub 1 since negative)
            input = int(input) - 1;
        }
        else
        {
            //Round up (truncate and add 1)
            input = int(input) + 1;
        }
    }
    else
    {
        if (input < 0)
        {
            //Round to .5 (truncate and sub .5 since negative)
            input = int(input) - 0.5;
        }
        else
        {
            //Round to .5 (truncate and add .5)
            input = int(input) + 0.5;
        }
    }
    return input;
}

float Formulas::round2Places(float input)
{
    //Move decimal point over two places, add .5 to round, and truncate
    int round = int(input * 100 + .5);
    //Convert back to float
    input = (float)round/100;
    return input;
}

void Formulas::calculateWeightDistributions()
{
    //Pointers to needed line edits
    QLineEdit* curbWeightLE = ui->vehicleLookup->findChild<QLineEdit*>("CurbWeightLineEdit");
    QLineEdit* weightDistributionLE = ui->vehicleLookup->findChild<QLineEdit*>("WeightDistributionLineEdit");
    QLineEdit* rearLeftWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearLeftWeight");
    QLineEdit* rearRightWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearRightWeight");
    QLineEdit* frontLeftWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontLeftWeight");
    QLineEdit* frontRightWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontRightWeight");
    QLineEdit* rearAxleWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearAxleWeight");
    QLineEdit* frontAxleWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontAxleWeight");
    QLineEdit* overallWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("overallWeight");

    //Make sure curbWeightLE and weightDistributionLE have values
    if ((curbWeightLE->text() != "") && ((weightDistributionLE->text().length()==4)||(weightDistributionLE->text().length()==5)))
    {
        //Variables for weight distribution
        int frontDist, rearDist;
        float overallWeight, frontAxleWeight, rearAxleWeight, frontTireWeight, rearTireWeight;

        //Get values
        overallWeight = curbWeightLE->text().toFloat();
        frontDist = weightDistributionLE->text().split("/")[0].toInt();
        rearDist = weightDistributionLE->text().split("/")[1].toInt();

        //Calculate values
        frontAxleWeight = roundPt5(overallWeight * (frontDist/100.0));
        rearAxleWeight = roundPt5(overallWeight * (rearDist/100.0));

        frontTireWeight = roundPt5(frontAxleWeight/2);
        rearTireWeight = roundPt5(rearAxleWeight/2);

        //Update line edits with new values
        rearLeftWeightLE->setText(QString::number(rearTireWeight));
        rearRightWeightLE->setText(QString::number(rearTireWeight));
        frontLeftWeightLE->setText(QString::number(frontTireWeight));
        frontRightWeightLE->setText(QString::number(frontTireWeight));
        rearAxleWeightLE->setText(QString::number(rearAxleWeight));
        frontAxleWeightLE->setText(QString::number(frontAxleWeight));
        overallWeightLE->setText(QString::number(overallWeight));


    }

}

void Formulas::calculateAxleAndTireWeights()
{
    //Pointers to needed line edits
    QLineEdit* weightDistributionLE = ui->vehicleLookup->findChild<QLineEdit*>("WeightDistributionLineEdit");
    QLineEdit* rearLeftWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearLeftWeight");
    QLineEdit* rearRightWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearRightWeight");
    QLineEdit* frontLeftWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontLeftWeight");
    QLineEdit* frontRightWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontRightWeight");
    QLineEdit* rearAxleWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearAxleWeight");
    QLineEdit* frontAxleWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontAxleWeight");
    QLineEdit* overallWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("overallWeight");

    //Make sure overallWeightLE and weightDistributionLE have values
    if ((overallWeightLE->text() != "") && ((weightDistributionLE->text().length()==4)||(weightDistributionLE->text().length()==5)))
    {
        //Variables for weight distribution
        int frontDist, rearDist;
        float overallWeight, frontAxleWeight, rearAxleWeight, frontTireWeight, rearTireWeight;

        //Get values
        overallWeight = overallWeightLE->text().toFloat();
        frontDist = weightDistributionLE->text().split("/")[0].toInt();
        rearDist = weightDistributionLE->text().split("/")[1].toInt();

        //Calculate values
        frontAxleWeight = roundPt5(overallWeight * (frontDist/100.0));
        rearAxleWeight = roundPt5(overallWeight * (rearDist/100.0));

        frontTireWeight = roundPt5(frontAxleWeight/2);
        rearTireWeight = roundPt5(rearAxleWeight/2);

        //Update line edits with new values
        rearLeftWeightLE->setText(QString::number(rearTireWeight));
        rearRightWeightLE->setText(QString::number(rearTireWeight));
        frontLeftWeightLE->setText(QString::number(frontTireWeight));
        frontRightWeightLE->setText(QString::number(frontTireWeight));
        rearAxleWeightLE->setText(QString::number(rearAxleWeight));
        frontAxleWeightLE->setText(QString::number(frontAxleWeight));
    }

}

/**
 * @brief Formulas::calculateComLong
 *
 * This method calculates the Horizontal Center of Mass using the variables front axle weight, wheelbase,
 * and overall weight.
 */
void Formulas::calculateComLong()
{
    //pointer to front axel weight line edit
    QLineEdit* frontAxleWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontAxleWeight");
    //pointer to wheelbase lenght line edit
    QLineEdit* wheelBaseLE = ui->vehicleLookup->findChild<QLineEdit*>("WBLineEdit");
    //pointer to total weight of the vehicle line edit
    QLineEdit* overallWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("overallWeight");
    //pointer to horizontal center of mass line edit
    QLineEdit* comLongLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("comLong");
    QLineEdit* comLongSolutionsLE = ui->formulaLayout->findChild<centerofmasssolutions*>()->findChild<QLineEdit*>("CoMLongLineEdit");

    if((frontAxleWeightLE->text() != "") && (wheelBaseLE->text() != "") && (overallWeightLE->text() != "")){


        float frontAxleWeight, wheelBase, overallWeight, comLong, roundedCOMlong;
        //get weight for the front axle
        frontAxleWeight = frontAxleWeightLE->text().toFloat();
        //get wheelbase langth
        wheelBase = wheelBaseLE->text().toFloat();
        //get total weight
        overallWeight = overallWeightLE->text().toFloat();
        //calculate the horizontal center of mass
        comLong = (frontAxleWeight * wheelBase) / overallWeight;
        //round the horizontal center of mass
        roundedCOMlong = roundPt5(comLong);
        //Update comLongLE edit with the value
        comLongLE->setText(QString::number(roundedCOMlong));
        comLongSolutionsLE->setText(QString::number(roundedCOMlong));

    }
}

/**
 * @brief Formulas::calculateComLatRight
 *
 */
void Formulas::calculateComLatRight()
{
    QLineEdit* overallWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("overallWeight");
    QLineEdit* rearRightWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearRightWeight");
    QLineEdit* frontRightWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontRightWeight");
    QLineEdit* trackWidthLE = ui->vehicleLookup->findChild<QLineEdit*>("FTWLineEdit");
    QLineEdit* comLatRightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("comLatRight");
    QLineEdit* comLatRightSolutionsLE = ui->formulaLayout->findChild<centerofmasssolutions*>()->findChild<QLineEdit*>("CoMLatRightLineEdit");

    //Make sure all boxes have a value
    if ((overallWeightLE->text() != "") && (trackWidthLE->text() != "") && (rearRightWeightLE->text() != "") && (frontRightWeightLE->text() != ""))
    {
        float rightSideWeight, trackWidth, overallWeight, comLatRight;

        //Get values from line edits
        rightSideWeight = frontRightWeightLE->text().toFloat();
        rightSideWeight = rightSideWeight + rearRightWeightLE->text().toFloat();
        trackWidth = trackWidthLE->text().toFloat();
        overallWeight = overallWeightLE->text().toFloat();

        //Calculate CoM
        comLatRight = roundPt5((rightSideWeight * trackWidth)/overallWeight);

        //Update CoM line edits
        comLatRightLE->setText(QString::number(comLatRight));
        comLatRightSolutionsLE->setText(QString::number(comLatRight));
    }
}
void Formulas::calculateComLatLeft()
{
    QLineEdit* overallWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("overallWeight");
    QLineEdit* rearLeftWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearLeftWeight");
    QLineEdit* frontLeftWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontLeftWeight");
    QLineEdit* trackWidthLE = ui->vehicleLookup->findChild<QLineEdit*>("FTWLineEdit");
    QLineEdit* comLatLeftLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("comLatLeft");
    QLineEdit* comLatLeftSolutionsLE = ui->formulaLayout->findChild<centerofmasssolutions*>()->findChild<QLineEdit*>("CoMLatLeftLineEdit");

    //Make sure all boxes have a value
    if ((overallWeightLE->text() != "") && (trackWidthLE->text() != "") && (rearLeftWeightLE->text() != "") && (frontLeftWeightLE->text() != ""))
    {
        float leftSideWeight, trackWidth, overallWeight, comLatLeft;

        //Get values from line edits
        leftSideWeight = frontLeftWeightLE->text().toFloat();
        leftSideWeight = leftSideWeight + rearLeftWeightLE->text().toFloat();
        trackWidth = trackWidthLE->text().toFloat();
        overallWeight = overallWeightLE->text().toFloat();

        //Calculate CoM
        comLatLeft = roundPt5((leftSideWeight * trackWidth)/overallWeight);

        //Update CoM line edits
        comLatLeftLE->setText(QString::number(comLatLeft));
        comLatLeftSolutionsLE->setText(QString::number(comLatLeft));

    }
}
void Formulas::calculateComHt()
{
    QLineEdit* overallWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("overallWeight");
    QLineEdit* frontAxleWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontAxleWeight");
    QLineEdit* wheelBaseLE = ui->vehicleLookup->findChild<QLineEdit*>("WBLineEdit");
    QLineEdit* heightCenterFrontWheelsLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("heightCenterFrontWheels");
    QLineEdit* heightCenterRearWheelsRaisedLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("heightCenterRearWheelsRaised");
    QLineEdit* weightFrontWheelsRearRaisedLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("weightFrontWheelsRearRaised");
    QLineEdit* comHtLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("comHt");
    QLineEdit* comHtSolutionsLE = ui->formulaLayout->findChild<centerofmasssolutions*>()->findChild<QLineEdit*>("CoMHtLineEdit");

    //Make sure all boxes have a value
    if ((overallWeightLE->text() != "") && (frontAxleWeightLE->text() != "") && (wheelBaseLE->text() != "") && (heightCenterFrontWheelsLE->text() != "") && (heightCenterRearWheelsRaisedLE->text() != "") && (weightFrontWheelsRearRaisedLE->text() != ""))
    {
        float overallWeight, frontAxleWeight, wheelBase, heightCenterFrontWheels, heightCenterRearWheelsRaised, weightFrontWheelsRearRaised, comHt, heightDiff;

        //Get values from line edits
        overallWeight = overallWeightLE->text().toFloat();
        frontAxleWeight = frontAxleWeightLE->text().toFloat();
        wheelBase = wheelBaseLE->text().toFloat();
        heightCenterFrontWheels = heightCenterFrontWheelsLE->text().toFloat();
        heightCenterRearWheelsRaised = heightCenterRearWheelsRaisedLE->text().toFloat();
        weightFrontWheelsRearRaised = weightFrontWheelsRearRaisedLE->text().toFloat();

        //Calculate CoM
        heightDiff = heightCenterRearWheelsRaised - heightCenterFrontWheels;
        comHt = roundPt5(heightCenterFrontWheels + (((weightFrontWheelsRearRaised-frontAxleWeight)*wheelBase*qSqrt(wheelBase*wheelBase-(heightDiff*heightDiff)))/(overallWeight*heightDiff)));

        //Update CoM line edits
        comHtLE->setText(QString::number(comHt));
        comHtSolutionsLE->setText(QString::number(comHt));
    }
}

/**
 * @brief Formulas::calculateMinimumSpeed
 *
 * This method calculates the Minimum Speed using variables skid distance, and acceleration/drag coefficient.
 */
void Formulas::calculateMinimumSpeed() {

    QLineEdit* skidDistanceLE = ui->formulaLayout->findChild<MinimumSpeed*>()->findChild<QLineEdit*>("SkidMarkLengthLineEdit");
    QLineEdit* AccelDragLE = ui->formulaLayout->findChild<MinimumSpeed*>()->findChild<QLineEdit*>("AccelDragFLineEdit");
    QLineEdit* minimumSpeedLE = ui->formulaLayout->findChild<centerofmasssolutions*>()->findChild<QLineEdit*>("minimumSpeedLineEdit");

    if((skidDistanceLE->text() != "") && (AccelDragLE->text() != "")){

        float skidDistance, AccelDrag, minSpeed, roundedMINspeed;

        skidDistance = skidDistanceLE->text().toFloat();
        AccelDrag = AccelDragLE->text().toFloat();

        minSpeed = 30 * skidDistance * AccelDrag;
        minSpeed = qSqrt(minSpeed);

        roundedMINspeed = round2Places(minSpeed);

        minimumSpeedLE->setText(QString::number(roundedMINspeed));
    }
}

/**
 * @brief Formulas::calculateVelocity
 *
 * This method calculates Velocity using variable Minimum Speed
 */
void Formulas::calculateVelocity() {

    QLineEdit* minimumSpeedLE = ui->formulaLayout->findChild<centerofmasssolutions*>()->findChild<QLineEdit*>("minimumSpeedLineEdit");
    QLineEdit* velocityLE = ui->formulaLayout->findChild<centerofmasssolutions*>()->findChild<QLineEdit*>("velocityLineEdit");

    if(minimumSpeedLE->text() != ""){
        //constant used to convert the minimum speed into velocity
        const float conversion = 1.466;

        float velocity, speed, roundedVelocity;

        speed = minimumSpeedLE->text().toFloat();

        velocity = conversion * speed;

        roundedVelocity = round2Places(velocity);

        velocityLE->setText(QString::number(roundedVelocity));

    }
}

void Formulas::calculateAxleAndOverallWeight()
{
    //Pointers to needed line edits
    QLineEdit* rearLeftWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearLeftWeight");
    QLineEdit* rearRightWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearRightWeight");
    QLineEdit* frontLeftWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontLeftWeight");
    QLineEdit* frontRightWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontRightWeight");
    QLineEdit* rearAxleWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearAxleWeight");
    QLineEdit* frontAxleWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontAxleWeight");
    QLineEdit* overallWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("overallWeight");

    //Make sure tire weights have values
    if ((rearLeftWeightLE->text() != "") && (rearRightWeightLE->text() != "") && (frontLeftWeightLE->text() != "") && (frontRightWeightLE->text() != ""))
    {
        //Variables
        float overallWeight, frontAxleWeight, rearAxleWeight, frontLeftWeight, rearLeftWeight, frontRightWeight, rearRightWeight;

        //Get values
        frontLeftWeight = frontLeftWeightLE->text().toFloat();
        frontRightWeight = frontRightWeightLE->text().toFloat();
        rearLeftWeight = rearLeftWeightLE->text().toFloat();
        rearRightWeight = rearRightWeightLE->text().toFloat();

        //Calculate values
        frontAxleWeight = frontRightWeight + frontLeftWeight;
        rearAxleWeight = rearRightWeight + rearLeftWeight;
        overallWeight = frontAxleWeight + rearAxleWeight;

        //Update line edits with new values
        rearAxleWeightLE->setText(QString::number(rearAxleWeight));
        frontAxleWeightLE->setText(QString::number(frontAxleWeight));
        overallWeightLE->setText(QString::number(overallWeight));
    }
}

//****************** NOTE: THESE METHODS ARE FOR UNIT TESTING *****************************************

//###################################### SETTERS (for variables input by the user/program) #################################

/**
 * @brief Formulas::SETcurbWeightLE
 * @param w
 */
void Formulas::SETcurbWeightLE (QString input){
    QLineEdit* curbWeightLE = ui->vehicleLookup->findChild<QLineEdit*>("CurbWeightLineEdit");
    curbWeightLE->setText(input);
}

void Formulas::SETweightDistributionLE (QString input){
    QLineEdit* weightDistributionLE = ui->vehicleLookup->findChild<QLineEdit*>("WeightDistributionLineEdit");
    weightDistributionLE->setText(input);
}

void Formulas::SETfrontAxleWeightLE (QString input){
    QLineEdit* frontAxleWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontAxleWeight");
    frontAxleWeightLE->setText(input);
}

void Formulas::SETwheelBaseLE (QString input) {
    QLineEdit* wheelBaseLE = ui->vehicleLookup->findChild<QLineEdit*>("WBLineEdit");
    wheelBaseLE->setText(input);
}
//KEEP this method?
void Formulas::SEToverallWeightLE (QString input){
    QLineEdit* overallWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("overallWeight");
    overallWeightLE->setText(input);
}

void Formulas::SETrearRightWeightLE (QString input) {
    QLineEdit* rearRightWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearRightWeight");
    rearRightWeightLE->setText(input);
}

void Formulas::SETfrontRightWeightLE (QString input) {
    QLineEdit* frontRightWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontRightWeight");
    frontRightWeightLE->setText(input);
}

void Formulas::SETtrackWidthLE (QString input) {
        QLineEdit* trackWidthLE = ui->vehicleLookup->findChild<QLineEdit*>("FTWLineEdit");
        trackWidthLE->setText(input);
}

void Formulas::SETrearLeftWeightLE (QString input){
        QLineEdit* rearLeftWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearLeftWeight");
        rearLeftWeightLE->setText(input);
}
void Formulas::SETfrontLeftWeightLE (QString input){
        QLineEdit* frontLeftWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontLeftWeight");
        frontLeftWeightLE->setText(input);
}
void Formulas::SETheightCenterFrontWheelsLE (QString input){
    QLineEdit* heightCenterFrontWheelsLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("heightCenterFrontWheels");
    heightCenterFrontWheelsLE->setText(input);
}
void Formulas::SETheightCenterRearWheelsRaisedLE (QString input){
    QLineEdit* heightCenterRearWheelsRaisedLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("heightCenterRearWheelsRaised");
    heightCenterRearWheelsRaisedLE->setText(input);
}
void Formulas::SETweightFrontWheelsRearRaisedLE (QString input){
    QLineEdit* weightFrontWheelsRearRaisedLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("weightFrontWheelsRearRaised");
    weightFrontWheelsRearRaisedLE->setText(input);
}
void Formulas::SETskidDistanceLE (QString input) {
    QLineEdit* skidDistanceLE = ui->formulaLayout->findChild<MinimumSpeed*>()->findChild<QLineEdit*>("SkidMarkLengthLineEdit");
    skidDistanceLE->setText(input);
}
void Formulas::SETAccelDragLE (QString input) {
    QLineEdit* AccelDragLE = ui->formulaLayout->findChild<MinimumSpeed*>()->findChild<QLineEdit*>("AccelDragFLineEdit");
    AccelDragLE->setText(input);
}
void Formulas::SETrearAxleWeightLE (QString input){
    QLineEdit* rearAxleWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearAxleWeight");
    rearAxleWeightLE->setText(input);
}
void Formulas::SETminimumSpeedLE(QString input) {
    QLineEdit* minimumSpeedLE = ui->formulaLayout->findChild<centerofmasssolutions*>()->findChild<QLineEdit*>("minimumSpeedLineEdit");
    minimumSpeedLE->setText(input);
}



//################################ GETTERS (for variables that are calculated) ##################################################
float Formulas::GETrearLeftWeightLEval() {
    QLineEdit* rearLeftWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearLeftWeight");
    return rearLeftWeightLE->text().toFloat();
}

float Formulas::GETrearRightWeightLEval() {
    QLineEdit* rearRightWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearRightWeight");
    return rearRightWeightLE->text().toFloat();
}

float Formulas::GETfrontLeftWeightLEval(){
        QLineEdit* frontLeftWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontLeftWeight");
        return frontLeftWeightLE->text().toFloat();
}
float Formulas::GETfrontRightWeightLEval(){
    QLineEdit* frontRightWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontRightWeight");
    return frontRightWeightLE->text().toFloat();
}
float Formulas::GETrearAxleWeightLEval(){
        QLineEdit* rearAxleWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("rearAxleWeight");
        return rearAxleWeightLE->text().toFloat();
}
float Formulas::GETfrontAxleWeightLEval(){
    QLineEdit* frontAxleWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("frontAxleWeight");
    return frontAxleWeightLE->text().toFloat();
}
float Formulas::GEToverallWeightLEval(){
        QLineEdit* overallWeightLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("overallWeight");
        return overallWeightLE->text().toFloat();
}
float Formulas::GETcomLongSolutionsLEval(){
    QLineEdit* comLongSolutionsLE = ui->formulaLayout->findChild<centerofmasssolutions*>()->findChild<QLineEdit*>("CoMLongLineEdit");
    return comLongSolutionsLE->text().toFloat();
}
float Formulas::GETtrackWidthLEval() {
    QLineEdit* trackWidthLE = ui->vehicleLookup->findChild<QLineEdit*>("FTWLineEdit");
    return trackWidthLE->text().toFloat();
}
float Formulas::GETcomLatRightSolutionsLEval() {
    QLineEdit* comLatRightSolutionsLE = ui->formulaLayout->findChild<centerofmasssolutions*>()->findChild<QLineEdit*>("CoMLatRightLineEdit");
    return comLatRightSolutionsLE->text().toFloat();
}
float Formulas::GETcomLatLeftSolutionsLEval(){
    QLineEdit* comLatLeftSolutionsLE = ui->formulaLayout->findChild<centerofmasssolutions*>()->findChild<QLineEdit*>("CoMLatLeftLineEdit");
    return comLatLeftSolutionsLE->text().toFloat();
}
float Formulas::GETwheelBaseLEval(){
    QLineEdit* wheelBaseLE = ui->vehicleLookup->findChild<QLineEdit*>("WBLineEdit");
    return wheelBaseLE->text().toFloat();
}
float Formulas::GETheightCenterFrontWheelsLEval() {
    QLineEdit* heightCenterFrontWheelsLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("heightCenterFrontWheels");
    return heightCenterFrontWheelsLE->text().toFloat();
}
float Formulas::GETheightCenterRearWheelsRaisedLEval(){
    QLineEdit* heightCenterRearWheelsRaisedLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("heightCenterRearWheelsRaised");
    return heightCenterRearWheelsRaisedLE->text().toFloat();
}
float Formulas::GETweightFrontWheelsRearRaisedLEval(){
    QLineEdit* weightFrontWheelsRearRaisedLE = ui->vehicleLookup->findChild<VehicleWeights*>()->findChild<QLineEdit*>("weightFrontWheelsRearRaised");
    return weightFrontWheelsRearRaisedLE->text().toFloat();
}
float Formulas::GETcomHtSolutionsLEval(){
    QLineEdit* comHtSolutionsLE = ui->formulaLayout->findChild<centerofmasssolutions*>()->findChild<QLineEdit*>("CoMHtLineEdit");
    return comHtSolutionsLE->text().toFloat();
}
float Formulas::GETskidDistanceLEval(){
    QLineEdit* skidDistanceLE = ui->formulaLayout->findChild<MinimumSpeed*>()->findChild<QLineEdit*>("SkidMarkLengthLineEdit");
    return skidDistanceLE->text().toFloat();
}
float Formulas::GETAccelDragLEval(){
    QLineEdit* AccelDragLE = ui->formulaLayout->findChild<MinimumSpeed*>()->findChild<QLineEdit*>("AccelDragFLineEdit");
    return AccelDragLE->text().toFloat();
}
float Formulas::GETminimumSpeedLEval(){
    QLineEdit* minimumSpeedLE = ui->formulaLayout->findChild<centerofmasssolutions*>()->findChild<QLineEdit*>("minimumSpeedLineEdit");
    return minimumSpeedLE->text().toFloat();
}
QString Formulas::GETweightDistributionLEval() {
    QLineEdit* weightDistributionLE = ui->vehicleLookup->findChild<QLineEdit*>("WeightDistributionLineEdit");
    return weightDistributionLE->text();
}
float Formulas::GETcurbWeightLEval() {
    QLineEdit* curbWeightLE = ui->vehicleLookup->findChild<QLineEdit*>("CurbWeightLineEdit");
    return curbWeightLE->text().toFloat();
}
float Formulas::GETvelocityLEval() {
    QLineEdit* velocityLE = ui->formulaLayout->findChild<centerofmasssolutions*>()->findChild<QLineEdit*>("velocityLineEdit");
    return velocityLE->text().toFloat();
}


//***********************************************************************************************************************************



//THESE METHODS CALL CALCULATION METHODS WHENEVER A SIGNAL IS EMMITTED
void Formulas::on_CurbWeightLineEdit_textChanged()
{
    calculateWeightDistributions();
}

void Formulas::on_WeightDistributionLineEdit_textChanged()
{
    calculateWeightDistributions();

}

void Formulas::on_rearLeftWeight_textChanged()
{
    calculateComLatLeft();
}
void Formulas::on_rearRightWeight_textChanged()
{
    calculateComLatRight();
}
void Formulas::on_frontRightWeight_textChanged()
{
    calculateComLatRight();
}
void Formulas::on_frontLeftWeight_textChanged()
{
    calculateComLatLeft();
}
void Formulas::on_rearLeftWeight_textEdited()
{
    calculateAxleAndOverallWeight();
}
void Formulas::on_rearRightWeight_textEdited()
{
    calculateAxleAndOverallWeight();
}
void Formulas::on_frontRightWeight_textEdited()
{
    calculateAxleAndOverallWeight();
}
void Formulas::on_frontLeftWeight_textEdited()
{
    calculateAxleAndOverallWeight();
}
void Formulas::on_overallWeight_textChanged()
{
    calculateComLatLeft();
    calculateComLatRight();
    calculateComLong();
    calculateComHt();
}
void Formulas::on_overallWeight_textEdited()
{
    calculateAxleAndTireWeights();
}
void Formulas::on_FTWLineEdit_textChanged()
{
    calculateComLatLeft();
    calculateComLatRight();
}

void Formulas::on_WBLineEdit_textChanged()
{
    calculateComLong();
    calculateComHt();
}
void Formulas::on_frontAxleWeight_textChanged()
{
    calculateComLong();
    calculateComHt();
}

void Formulas::on_SkidMarkLengthLineEdit_textChanged()
{
    calculateMinimumSpeed();
}

void Formulas::on_AccelDragFLineEdit_textChanged()
{
    calculateMinimumSpeed();
}

void Formulas::on_heightCenterFrontWheels_textChanged()
{
    calculateComHt();
}
void Formulas::on_heightCenterRearWheelsRaised_textChanged()
{
    calculateComHt();
}
void Formulas::on_weightFrontWheelsRearRaised_textChanged()
{
    calculateComHt();
}

void Formulas::on_minimumSpeedLineEdit_textChanged()
{
    calculateVelocity();
}

void Formulas::on_saveAsPDFButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Generated Report"), "",
        tr("PDF (*.pdf)"));
    if(fileName.isEmpty()) {
        fileName = "report.pdf";
    }
    QTextDocument doc;

    QPrinter printer;
    printer.setResolution(96);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::Letter);
    printer.setOutputFileName(fileName);
    printer.setPageMargins(0.75, 1, 0.75, 1, QPrinter::Inch);

    QString html = generateHtml();

    doc.setHtml(html);

    doc.setPageSize(QSizeF(printer.pageRect().size()));
    doc.print(&printer);
}

QString Formulas::generateHtml() {
    QString rando= "random";
    //Save VehicleWeights widget
    ui->vehicleLookup->findChild<VehicleWeights*>()->grab().save("vehicleWeights.png");
    QString notes = ui->formulaLayout->findChild<MinimumSpeed*>()->findChild<QPlainTextEdit*>("NotesPlainTextEdit")->toPlainText();

    notes.replace("<", "&lt;");
    notes.replace(">", "&gt;");

    //css style header
    QString html = "<style type=\"text/css\">";
    html += "h3 {font-size:20;} h4 {font-size:16;} table {font-size: 14; width=100%;}";
    html += "</style>";
    //vehicle
    html += "<h3>Vehicle 1</h3>";
    html += "<table border=1><tr><td><table><tr><td width=33%>";
    //Vehicle Specific Information
    html += "<h4>Vehicle Specific Information</h4>";
    html += "Year: " + ui->vehicleLookup->findChild<QComboBox*>("YearComboBox")->currentText() + "<br>";
    html += "Make: " + ui->vehicleLookup->findChild<QComboBox*>("SelectAMakeComboBox")->currentText() + "<br>";
    html += "Model: " + ui->vehicleLookup->findChild<QComboBox*>("SelectAModelComboBox")->currentText() + "<br>";
    html += "Trim: " + ui->vehicleLookup->findChild<QComboBox*>("SelectATrimComboBox")->currentText() + "<br>";
    html += "License Plate: " + ui->vehicleLookup->findChild<QLineEdit*>("LicensePlateLineEdit")->text() + "<br>";
    html += "Registration Year: " + ui->vehicleLookup->findChild<QLineEdit*>("RegistrationYearLineEdit")->text() + "<br>";
    html += "VIN: " + ui->vehicleLookup->findChild<QLineEdit*>("VINLineEdit")->text() + "<br>";
    html += "State: " + ui->vehicleLookup->findChild<QComboBox*>("StateComboBox")->currentText() + "<br>";
    html += "Color: " + ui->vehicleLookup->findChild<QLineEdit*>("ColorLineEdit")->text() + "<br>";
    html += "Body: " + ui->vehicleLookup->findChild<QLineEdit*>("BodyLineEdit")->text() + "<br>";
    html += "Top Speed: " + ui->vehicleLookup->findChild<QLineEdit*>("TopSpeedLineEdit")->text() + "<br>";
    html += "0 to 100 MPH: " + ui->vehicleLookup->findChild<QLineEdit*>("ZeroTo100MPHLineEdit")->text() + "<br>";
    html += "Drive: " + ui->vehicleLookup->findChild<QLineEdit*>("DriveLineEdit")->text() + "<br>";
    html += "Transmission: " + ui->vehicleLookup->findChild<QLineEdit*>("TransmissionLineEdit")->text() + "<br>";
    html += "Seats: " + ui->vehicleLookup->findChild<QLineEdit*>("SeatsLineEdit")->text() + "<br>";
    html += "Doors: " + ui->vehicleLookup->findChild<QLineEdit*>("DoorsLineEdit")->text() + "<br>";
    html += "GPM - hwy: " + ui->vehicleLookup->findChild<QLineEdit*>("GPMHwyLineEdit")->text() + "<br>";
    html += "GPM - mixed: " + ui->vehicleLookup->findChild<QLineEdit*>("GPMMixedLineEdit")->text() + "<br>";
    html += "GPM - city: " + ui->vehicleLookup->findChild<QLineEdit*>("GPMCityLineEdit")->text() + "<br>";
    html += "Fuel Capacity - G: " + ui->vehicleLookup->findChild<QLineEdit*>("FuelCapacityLineEdit")->text() + "<br>";
    html += "Sold in US: " + ui->vehicleLookup->findChild<QLineEdit*>("SoldInUSLineEdit")->text() + "<br>";
    html += "<img src=\"vehicleWeights.png\" alt=\"Vehicle Weights\" width=\"630\" height=\"340\">";
    html += "</td><td width=33%>";

    //Engine Information
    html += "<h4>Engine Information</h4>";
    html += "Position: " + ui->vehicleLookup->findChild<QLineEdit*>("PositionLineEdit")->text() + "<br>";
    html += "CC: " + ui->vehicleLookup->findChild<QLineEdit*>("CCLineEdit")->text() + "<br>";
    html += "Cylinders: " + ui->vehicleLookup->findChild<QLineEdit*>("CylindersLineEdit")->text() + "<br>";
    html += "Type: " + ui->vehicleLookup->findChild<QLineEdit*>("TypeLineEdit")->text() + "<br>";
    html += "Valves/Cylinder: " + ui->vehicleLookup->findChild<QLineEdit*>("ValvesPerCylinderLineEdit")->text() + "<br>";
    html += "Power ps: " + ui->vehicleLookup->findChild<QLineEdit*>("PowerPSLineEdit")->text() + "<br>";
    html += "Power rpm: " + ui->vehicleLookup->findChild<QLineEdit*>("PowerRPMLineEdit")->text() + "<br>";
    html += "Torque nm: " + ui->vehicleLookup->findChild<QLineEdit*>("TorqueNMLineEdit")->text() + "<br>";
    html += "Torque rpm: " + ui->vehicleLookup->findChild<QLineEdit*>("TorqueRPMLineEdit")->text() + "<br>";
    html += "Bore mm: " + ui->vehicleLookup->findChild<QLineEdit*>("BoreMMLineEdit")->text() + "<br>";
    html += "Stroke mm: " + ui->vehicleLookup->findChild<QLineEdit*>("StrokeMMLineEdit")->text() + "<br>";
    html += "Compression: " + ui->vehicleLookup->findChild<QLineEdit*>("CompressionLineEdit")->text() + "<br>";
    html += "Fuel: " + ui->vehicleLookup->findChild<QLineEdit*>("FuelLineEdit")->text() + "<br>";
    html += "</td><td width=33%>";

    //Vehicle Specs and Measurements
    html += "<h4>Specifications and Measurements</h4>" ;
    html += "Curb Weight: " + ui->vehicleLookup->findChild<QLineEdit*>("CurbWeightLineEdit")->text() + "<br>";
    html += "Wheelbase: " + ui->vehicleLookup->findChild<QLineEdit*>("WBLineEdit")->text() + "<br>";
    html += "Track Width Front: " + ui->vehicleLookup->findChild<QLineEdit*>("FTWLineEdit")->text() + "<br>";
    html += "Track Width Rear: " + ui->vehicleLookup->findChild<QLineEdit*>("RTWLineEdit")->text() + "<br>";
    html += "Overall Length: " + ui->vehicleLookup->findChild<QLineEdit*>("OLLineEdit")->text() + "<br>";
    html += "Overall Width: " + ui->vehicleLookup->findChild<QLineEdit*>("OWLineEdit")->text() + "<br>";
    html += "Overall Height: " + ui->vehicleLookup->findChild<QLineEdit*>("OHLineEdit")->text() + "<br>";
    html += "Weight Dist: " + ui->vehicleLookup->findChild<QLineEdit*>("WeightDistributionLineEdit")->text() + "<br>";
    html += "Bumper to Windshield: " + ui->vehicleLookup->findChild<QLineEdit*>("ALineEdit")->text() + "<br>";
    html += "Backlight to B Pillar: " + ui->vehicleLookup->findChild<QLineEdit*>("BLineEdit")->text() + "<br>";
    html += "Side Glass Height: " + ui->vehicleLookup->findChild<QLineEdit*>("CLineEdit")->text() + "<br>";
    html += "Side Glass to Edge: " + ui->vehicleLookup->findChild<QLineEdit*>("DLineEdit")->text() + "<br>";
    html += "Side Rails/Top: " + ui->vehicleLookup->findChild<QLineEdit*>("ELineEdit")->text() + "<br>";
    html += "Front Overhang: " + ui->vehicleLookup->findChild<QLineEdit*>("FLineEdit")->text() + "<br>";
    html += "Rear Overhang: " + ui->vehicleLookup->findChild<QLineEdit*>("GLineEdit")->text() + "<br>";
    html += "</td></tr></table></td></tr></table>";

    html += "<h3>Minimum Speed</h3>";
    html += "<table border=1><tr><td><table><tr><td width=33%>";
    html += "<h4>Variables</h4>";
    html += "Skid Mark Length (ft): " + ui->formulaLayout->findChild<MinimumSpeed*>()->findChild<QLineEdit*>("SkidMarkLengthLineEdit")->text() + "<br>";
    html += "Accel/Drag f: " + ui->formulaLayout->findChild<MinimumSpeed*>()->findChild<QLineEdit*>("AccelDragFLineEdit")->text() + "<br>";
    html += "</td><td width=33%>";
    html += "<h4>Formula</h4>";
    html += "Formula: S = <span>&#8730;<span style=\"text-decoration:overline;\">&nbsp;30 x D x f&nbsp;</span></span> <br>";
    html += "</td><td width=33%>";
    html += "<h4>Result</h4>";
    html += "Minimum Speed: " + ui->formulaLayout->findChild<centerofmasssolutions*>()->findChild<QLineEdit*>("minimumSpeedLineEdit")->text() + "<br>";
    html += "</td></tr></table></td></tr></table>";

    html += "<h3>Notes</h3>";
    html += "<table border=1><tr><td><table><tr><td width=100%>";
    html += notes + "<br>";
    html += "</td></tr></table></td></tr></table>";

    return html;
}
