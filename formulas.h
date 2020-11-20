#ifndef FORMULAS_H
#define FORMULAS_H

#include <QWidget>
#include <ui_formulas.h>
#include <QString>
QT_BEGIN_NAMESPACE
namespace Ui { class Formulas; }
QT_END_NAMESPACE



class Formulas : public QWidget
{
    Q_OBJECT

public:
    Formulas(QWidget *parent = nullptr);
    ~Formulas();
    void calculateWeightDistributions();
    void calculateAxleAndOverallWeight();
    void calculateAxleAndTireWeights();
    void calculateComLong();
    void calculateComLatRight();
    void calculateComLatLeft();
    void calculateComHt();
    void calculateMinimumSpeed();
    void calculateVelocity();
    float roundPt5(float input);
    float round2Places(float input);

    //SETTERS
    void SETcurbWeightLE (QString w);
    void SETweightDistributionLE (QString w);
    void SETfrontAxleWeightLE (QString input);
    void SETwheelBaseLE (QString input);
    void SEToverallWeightLE (QString input);
    void SETrearRightWeightLE (QString input);
    void SETfrontRightWeightLE (QString input);
    void SETtrackWidthLE (QString input);
    void SETrearLeftWeightLE (QString input);
    void SETfrontLeftWeightLE (QString input);
    void SETheightCenterFrontWheelsLE (QString input);
    void SETheightCenterRearWheelsRaisedLE (QString input);
    void SETweightFrontWheelsRearRaisedLE (QString input);
    void SETskidDistanceLE (QString input);
    void SETAccelDragLE (QString input);
    void SETrearAxleWeightLE (QString input);
    void SETminimumSpeedLE(QString input);


    //GETTERS
    float GETrearLeftWeightLEval();
    float GETrearRightWeightLEval();
    float GETfrontLeftWeightLEval();
    float GETfrontRightWeightLEval();
    float GETrearAxleWeightLEval();
    float GETfrontAxleWeightLEval();
    float GEToverallWeightLEval();
    float GETcomLongSolutionsLEval();
    float GETtrackWidthLEval();
    float GETcomLatRightSolutionsLEval();
    float GETcomLatLeftSolutionsLEval();
    float GETwheelBaseLEval();
    float GETheightCenterFrontWheelsLEval();
    float GETheightCenterRearWheelsRaisedLEval();
    float GETweightFrontWheelsRearRaisedLEval();
    float GETcomHtSolutionsLEval();
    float GETskidDistanceLEval();
    float GETAccelDragLEval();
    float GETminimumSpeedLEval();
    QString GETweightDistributionLEval();
    float GETcurbWeightLEval();
    float GETvelocityLEval();


private:
    Ui::Formulas_UI *ui;
    DatabaseConnection *db;
    QString generateHtml();

private slots:
        void on_WeightDistributionLineEdit_textChanged();
        void on_CurbWeightLineEdit_textChanged();
        void on_rearLeftWeight_textChanged();
        void on_rearRightWeight_textChanged();
        void on_frontRightWeight_textChanged();
        void on_frontLeftWeight_textChanged();
        void on_rearLeftWeight_textEdited();
        void on_rearRightWeight_textEdited();
        void on_frontRightWeight_textEdited();
        void on_frontLeftWeight_textEdited();
        void on_overallWeight_textChanged();
        void on_overallWeight_textEdited();
        void on_FTWLineEdit_textChanged();
        void on_WBLineEdit_textChanged();
        void on_frontAxleWeight_textChanged();
        void on_SkidMarkLengthLineEdit_textChanged();
        void on_AccelDragFLineEdit_textChanged();
        void on_heightCenterFrontWheels_textChanged();
        void on_heightCenterRearWheelsRaised_textChanged();
        void on_weightFrontWheelsRearRaised_textChanged();
        void on_minimumSpeedLineEdit_textChanged();
        void on_saveAsPDFButton_clicked();

friend class unitTests;


};


#endif // FORMULAS_H

