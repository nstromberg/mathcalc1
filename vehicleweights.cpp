#include "vehicleweights.h"
#include "ui_vehicleweights.h"
#include <QRegExpValidator>

VehicleWeights::VehicleWeights(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VehicleWeights)
{
    ui->setupUi(this);
    //Only allow positive numbers with or without .5
    ui->heightCenterFrontWheels->setValidator(new QRegExpValidator(QRegExp("[0-9]*\\.?5?"), ui->heightCenterFrontWheels));
    ui->heightCenterRearWheelsRaised->setValidator(new QRegExpValidator(QRegExp("[0-9]*\\.?5?"), ui->heightCenterRearWheelsRaised));
    ui->weightFrontWheelsRearRaised->setValidator(new QRegExpValidator(QRegExp("[0-9]*\\.?5?"), ui->weightFrontWheelsRearRaised));
    ui->frontLeftWeight->setValidator(new QRegExpValidator(QRegExp("[0-9]*\\.?5?"), ui->frontLeftWeight));
    ui->frontRightWeight->setValidator(new QRegExpValidator(QRegExp("[0-9]*\\.?5?"), ui->frontRightWeight));
    ui->rearLeftWeight->setValidator(new QRegExpValidator(QRegExp("[0-9]*\\.?5?"), ui->rearLeftWeight));
    ui->rearRightWeight->setValidator(new QRegExpValidator(QRegExp("[0-9]*\\.?5?"), ui->rearRightWeight));
    //Only allow positive numbers with an optional decimal part
    ui->overallWeight->setValidator(new QRegExpValidator(QRegExp("[0-9]*\\.?[0-9]*"), ui->rearRightWeight));
}

VehicleWeights::~VehicleWeights()
{
    delete ui;
}
