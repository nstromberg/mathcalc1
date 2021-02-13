#include "VehicleLookUp.h"
#include "ui_VehicleLookUp.h"
#include <QRegExpValidator>

VehicleLookUp::VehicleLookUp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VehicleLookUp_UI)
{
    ui->setupUi(this);
    //Only allow positive integers
    ui->CurbWeightLineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), ui->CurbWeightLineEdit));
    ui->FTWLineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), ui->FTWLineEdit));
    ui->WBLineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), ui->WBLineEdit));
    //Only allow positive integers separated by a /
    ui->WeightDistributionLineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9]/[0-9][0-9]"), ui->WeightDistributionLineEdit));

    //Connect to database
    db = new DatabaseConnection();
    db->establish_database_connection();


    //Get all vehicle years
    QString getYears = "SELECT model_year FROM VEHICLE_SPECS_merge GROUP BY model_year";
    std::vector<std::vector<QString>> years = db->fetch_data_from_server(getYears);

    //Add years in descending order to the vehicle select year combobox

   // ui->YearComboBox->blockSignals(true);
    for (size_t i = years.size(); i > 0; i--)
    {
        ui->YearComboBox->addItem(years[i - 1][0]);
    }



    //Get all vehicle years for second query
    QString getCvsYears = "SELECT Year FROM VEHICLE_SPECS_ADDITIONAL GROUP BY Year";
    std::vector<std::vector<QString>> cvsYears = db->fetch_data_from_server(getCvsYears);

    //Add years in descending order to the vehicle select year combobox

   // ui->YearComboBox->blockSignals(true);
    for (size_t i = cvsYears.size(); i > 0; i--)
    {
        ui->CVS_YearComboBox->addItem(cvsYears[i - 1][0]);
    }

}

VehicleLookUp::~VehicleLookUp()
{
    delete ui;
}

void VehicleLookUp::on_YearComboBox_currentIndexChanged(const QString &year)
{
    if (year != QString("Select a Year"))
    {
        /*
        Empty make, model, and trim combo boxes
        when a new year is selected.
        Turn off signals so as not to trigger
        currentIndexChanged functions for other
        combo boxes while editing their items.
        */

        //Empty the Make combo box.
        ui->SelectAMakeComboBox->blockSignals(true);
        int makeLength = ui->SelectAMakeComboBox->count();
        ui->SelectAMakeComboBox->setCurrentIndex(0);
        for (int i = makeLength - 1; i > 0; i--)
        {
            ui->SelectAMakeComboBox->removeItem(i);
        }
        ui->SelectAMakeComboBox->blockSignals(false);

        //Empty the Model combo box
        ui->SelectAModelComboBox->blockSignals(true);
        int modelLength = ui->SelectAModelComboBox->count();
        ui->SelectAModelComboBox->setCurrentIndex(0);
        for (int i = modelLength - 1; i > 0; i--)
        {
            ui->SelectAModelComboBox->removeItem(i);
        }
        ui->SelectAModelComboBox->blockSignals(false);

        //Empty the Trim combo box
        ui->SelectATrimComboBox->blockSignals(true);
        int trimLength = ui->SelectATrimComboBox->count();
        ui->SelectATrimComboBox->setCurrentIndex(0);
        for (int i = trimLength - 1; i > 0; i--)
        {
            ui->SelectATrimComboBox->removeItem(i);
        }
        ui->SelectATrimComboBox->blockSignals(false);

        //Get all vehicle makes for selected year
        QString getMakes = "SELECT model_make_id FROM VEHICLE_SPECS_merge WHERE model_year = " + year + " GROUP BY model_make_id";
        std::vector<std::vector<QString>> makes = db->fetch_data_from_server(getMakes);

        //Populate the vehicle make combo box with
        //the retrieved vehicles.
        for (size_t i = 0; i < makes.size(); i++)
        {
            ui->SelectAMakeComboBox->addItem(makes[i][0]);
        }
    }
}




void VehicleLookUp::on_SelectAMakeComboBox_currentIndexChanged(const QString &make)
{
    if (make != QString("Select a Make"))
    {
        /*
        Empty model and trim combo boxes
        when a new make is selected.
        Turn off signals so as not to trigger
        currentIndexChanged functions for other
        combo boxes while editing their items.
        */

        //Empty the Model combo box
        ui->SelectAModelComboBox->blockSignals(true);
        int modelLength = ui->SelectAModelComboBox->count();
        ui->SelectAModelComboBox->setCurrentIndex(0);
        for (int i = modelLength - 1; i > 0; i--)
        {
            ui->SelectAModelComboBox->removeItem(i);
        }
        ui->SelectAModelComboBox->blockSignals(false);

        //Empty the Trim combo box
        ui->SelectATrimComboBox->blockSignals(true);
        int trimLength = ui->SelectATrimComboBox->count();
        ui->SelectATrimComboBox->setCurrentIndex(0);
        for (int i = trimLength - 1; i > 0; i--)
        {
            ui->SelectATrimComboBox->removeItem(i);
        }
        ui->SelectATrimComboBox->blockSignals(false);

        //Get all vehicle models for particular year and make
        QString year = ui->YearComboBox->currentText();
        QString makeLower = make.toLower();
        QString makeUpper = make.toUpper();
        QString makeUpperFirst = makeLower;
        makeUpperFirst[0] = makeUpperFirst[0].toUpper();

        QString getModels = "SELECT model_name FROM VEHICLE_SPECS_merge WHERE model_year = " + year + " AND (model_make_id = '" + makeLower + "' OR model_make_id = '" + makeUpper + "' OR model_make_id = '" + makeUpperFirst + "') GROUP BY model_name";
        std::vector<std::vector<QString>> models = db->fetch_data_from_server(getModels);

        //Populate the vehicle model combo box with
        //the retrieved vehicles.
        for (size_t i = 0; i < models.size(); i++)
        {
            ui->SelectAModelComboBox->addItem(models[i][0]);
        }
    }
}

void VehicleLookUp::on_SelectAModelComboBox_currentIndexChanged(const QString &model)
{
    if (model != QString("Select a Model"))
    {
        /*
        Empty the trim combo box when a new
        year is selected.
        Turn off signals so as not to trigger
        currentIndexChanged functions for other
        combo boxes while editing their items.
        */

        //Empty the Trim combo box
        ui->SelectATrimComboBox->blockSignals(true);
        int trimLength = ui->SelectATrimComboBox->count();
        ui->SelectATrimComboBox->setCurrentIndex(0);
        for (int i = trimLength - 1; i > 0; i--)
        {
            ui->SelectATrimComboBox->removeItem(i);
        }
        ui->SelectATrimComboBox->blockSignals(false);

        //Get all vehicle trims for particular year, make, and model
        QString year = ui->YearComboBox->currentText();
        QString make = ui->SelectAMakeComboBox->currentText();
        QString makeLower = make.toLower();
        QString makeUpper = make.toUpper();
        QString makeUpperFirst = makeLower;
        makeUpperFirst[0] = makeUpperFirst[0].toUpper();


        QString getVehicles = "SELECT model_trim FROM VEHICLE_SPECS_merge WHERE model_year = " + year + " AND (model_make_id = '" + makeLower + "' OR model_make_id = '" + makeUpper + "' OR model_make_id = '" + makeUpperFirst + "') AND model_name = '" + model + "'";
        std::vector<std::vector<QString>> vehicles = db->fetch_data_from_server(getVehicles);

        //Populate the vehicle trim combo box with
        //the retrieved vehicles.
        for (size_t i = 0; i < vehicles.size(); i++)
        {
            ui->SelectATrimComboBox->addItem(vehicles[i][0]);
        }
    }
}



void VehicleLookUp::on_pushButton_clicked()
{
    QString year = ui->YearComboBox->currentText();
    QString make = ui->SelectAMakeComboBox->currentText();
    QString model = ui->SelectAModelComboBox->currentText();
    QString trim = ui->SelectATrimComboBox->currentText();


    


    //filling in data using query results

    if (trim != "Select a Trim") {
        //Get all data for selected year/make/model/trim from database
    QString getVehicleData = "SELECT * FROM VEHICLE_SPECS_merge WHERE model_year = " + year + " AND model_make_id = '" + make + "' AND model_name = '" + model + "' AND model_trim = '" + trim + "' GROUP BY model_trim";
    std::vector<std::vector<QString>> vehicleDataDB = db->fetch_data_from_server(getVehicleData);
    QVector<QString> vehicleData = QVector<QString>::fromStdVector(vehicleDataDB[0]);
        
        
        //Filling in the line edits using the query results
        ui->BodyLineEdit->setText(vehicleData[4]);
        ui->TopSpeedLineEdit->setText(vehicleData[18]);
        ui->ZeroTo100MPHLineEdit->setText(vehicleData[19]);
        ui->DriveLineEdit->setText(vehicleData[20]);
        ui->TransmissionLineEdit->setText(vehicleData[21]);
        ui->SeatsLineEdit->setText(vehicleData[22]);
        ui->DoorsLineEdit->setText(vehicleData[23]);
        ui->GPMHwyLineEdit->setText(vehicleData[29]);
        ui->GPMMixedLineEdit->setText(vehicleData[30]);
        ui->GPMCityLineEdit->setText(vehicleData[31]);
        ui->FuelCapacityLineEdit->setText(vehicleData[32]);
        ui->SoldInUSLineEdit->setText(vehicleData[33]);
        ui->PositionLineEdit->setText(vehicleData[5]);
        ui->CCLineEdit->setText(vehicleData[6]);
        ui->CylindersLineEdit->setText(vehicleData[7]);
        ui->TypeLineEdit->setText(vehicleData[8]);
        ui->ValvesPerCylinderLineEdit->setText(vehicleData[9]);
        ui->PowerPSLineEdit->setText(vehicleData[10]);
        ui->PowerRPMLineEdit->setText(vehicleData[11]);
        ui->TorqueNMLineEdit->setText(vehicleData[12]);
        ui->TorqueRPMLineEdit->setText(vehicleData[13]);
        ui->BoreMMLineEdit->setText(vehicleData[14]);
        ui->StrokeMMLineEdit->setText(vehicleData[15]);
        ui->CompressionLineEdit->setText(vehicleData[16]);
        ui->FuelLineEdit->setText(vehicleData[17]);
        ui->CurbWeightLineEdit->setText(vehicleData[43]);

        if (vehicleData[28] != ""){
            int wheelbase = vehicleData[28].toInt() / 10;
           // qDebug() << QString::number(wheelbase);
            ui->WBLineEdit->setText(QString::number(wheelbase));
        }

        ui->FTWLineEdit->setText(vehicleData[44]);
        ui->RTWLineEdit->setText(vehicleData[45]);
        ui->OLLineEdit->setText(vehicleData[25]);
        ui->OWLineEdit->setText(vehicleData[26]);
        ui->OHLineEdit->setText(vehicleData[27]);
        ui->WeightDistributionLineEdit->setText(vehicleData[46]);

    }

}

void VehicleLookUp::on_CVS_YearComboBox_currentIndexChanged(const QString &year)
{
    if (year != QString("Select a Year"))
    {
        /*
        Empty make, model, and trim combo boxes
        when a new year is selected.
        Turn off signals so as not to trigger
        currentIndexChanged functions for other
        combo boxes while editing their items.
        */

        //Empty the Make combo box.
        ui->CVS_MakeComboBox->blockSignals(true);
        int makeLength = ui->CVS_MakeComboBox->count();
        ui->CVS_MakeComboBox->setCurrentIndex(0);
        for (int i = makeLength - 1; i > 0; i--)
        {
            ui->CVS_MakeComboBox->removeItem(i);
        }
        ui->CVS_MakeComboBox->blockSignals(false);

        //Empty the Model combo box
        ui->CVS_ModelComboBox->blockSignals(true);
        int modelLength = ui->SelectAModelComboBox->count();
        ui->CVS_ModelComboBox->setCurrentIndex(0);
        for (int i = modelLength - 1; i > 0; i--)
        {
            ui->CVS_ModelComboBox->removeItem(i);
        }
        ui->CVS_ModelComboBox->blockSignals(false);

        //Get all vehicle makes for selected year
        QString getMakes = "SELECT Make FROM VEHICLE_SPECS_ADDITIONAL WHERE Year = " + year + " GROUP BY Make";
        std::vector<std::vector<QString>> makes = db->fetch_data_from_server(getMakes);

        //Populate the vehicle make combo box with
        //the retrieved vehicles.
        for (size_t i = 0; i < makes.size(); i++)
        {
            ui->CVS_MakeComboBox->addItem(makes[i][0]);
        }
    }
}

void VehicleLookUp::on_CVS_MakeComboBox_currentIndexChanged(const QString &make)
{
    if (make != QString("Select a Make"))
    {
        /*
        Empty model and trim combo boxes
        when a new make is selected.
        Turn off signals so as not to trigger
        currentIndexChanged functions for other
        combo boxes while editing their items.
        */

        //Empty the Model combo box
        ui->CVS_ModelComboBox->blockSignals(true);
        int modelLength = ui->CVS_ModelComboBox->count();
        ui->CVS_ModelComboBox->setCurrentIndex(0);
        for (int i = modelLength - 1; i > 0; i--)
        {
            ui->CVS_ModelComboBox->removeItem(i);
        }
        ui->CVS_ModelComboBox->blockSignals(false);


        //Get all vehicle models for particular year and make
        QString year = ui->CVS_YearComboBox->currentText();
        QString makeLower = make.toLower();
        QString makeUpper = make.toUpper();
        QString makeUpperFirst = makeLower;
        makeUpperFirst[0] = makeUpperFirst[0].toUpper();

        QString getModels = "SELECT Model FROM VEHICLE_SPECS_ADDITIONAL WHERE Year = " + year + " AND (Make = '" + makeLower + "' OR Make = '" + makeUpper + "' OR Make = '" + makeUpperFirst + "') GROUP BY Model";
        std::vector<std::vector<QString>> models = db->fetch_data_from_server(getModels);

        //Populate the vehicle model combo box with
        //the retrieved vehicles.
        for (size_t i = 0; i < models.size(); i++)
        {
            ui->CVS_ModelComboBox->addItem(models[i][0]);
        }
    }
}


//Button pushed for second query
void VehicleLookUp::on_pushButton_2_clicked()
{   //Getting user input from dropdown menus
    QString year = ui->CVS_YearComboBox->currentText();
    QString make = ui->CVS_MakeComboBox->currentText();
    QString model = ui->CVS_ModelComboBox->currentText();


    //Query for vehicle information after all search criteria is entered

    if (model != "Select a Model") {

        //Generate Query string, perform query, return results as a vector cointaining vectors strings


        QString get_extra_vehicle_data = "SELECT * FROM VEHICLE_SPECS_ADDITIONAL WHERE Year = " + year + " AND Make = '" + make + "' AND Model = '" + model + "' GROUP BY Model";
        std::vector<std::vector<QString>> extra_vehicle_data_db = db->fetch_data_from_server(get_extra_vehicle_data);

        //getting the first result of the query into a single vector of strings
        // QVector<QString> extra_vehicle_data = QVector<QString>(extra_vehicle_data_db[0].begin(), extra_vehicle_data_db[0].end());
        QVector<QString> extra_vehicle_data = QVector<QString>::fromStdVector(extra_vehicle_data_db[0]);

        //filling line edits with information from query results
        if (extra_vehicle_data[19] != ""){
                ui->DriveLineEdit->setText(extra_vehicle_data[19]);
        }

        if (ui->DoorsLineEdit->text() == ""){
                ui->DoorsLineEdit->setText(extra_vehicle_data[18]);
        }

        if (ui->WeightDistributionLineEdit->text() == ""){
                ui->WeightDistributionLineEdit->setText(extra_vehicle_data[17]);
        }

        if (ui->OHLineEdit->text() == ""){            
                ui->OHLineEdit->setText(extra_vehicle_data[5]);
        }

       if (ui->OWLineEdit->text() == ""){            
                ui->OWLineEdit->setText(extra_vehicle_data[4]);
       }

       if (ui->OLLineEdit->text() == ""){
                ui->OLLineEdit->setText(extra_vehicle_data[3]);

       }

       if (ui->RTWLineEdit->text() == ""){
                ui->RTWLineEdit->setText(extra_vehicle_data[16]);
       }

       if (ui->FTWLineEdit->text() == ""){
                ui->FTWLineEdit->setText(extra_vehicle_data[15]);
       }

       if (ui->WBLineEdit->text() == ""){
                ui->WBLineEdit->setText(extra_vehicle_data[6]);
       }

       if (ui->CurbWeightLineEdit->text() == ""){
                ui->CurbWeightLineEdit->setText(extra_vehicle_data[7]);
       }


           ui->ALineEdit->setText(extra_vehicle_data[8]);       


           ui->BLineEdit->setText(extra_vehicle_data[9]);


           ui->CLineEdit->setText(extra_vehicle_data[10]);


           ui->DLineEdit->setText(extra_vehicle_data[11]);


           ui->ELineEdit->setText(extra_vehicle_data[12]);


           ui->FLineEdit->setText(extra_vehicle_data[13]);


           ui->GLineEdit->setText(extra_vehicle_data[14]);

    }

}
