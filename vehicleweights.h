#ifndef VEHICLEWEIGHTS_H
#define VEHICLEWEIGHTS_H

#include <QWidget>

namespace Ui {
class VehicleWeights;
}

class VehicleWeights : public QWidget
{
    Q_OBJECT

public:
    explicit VehicleWeights(QWidget *parent = nullptr);
    ~VehicleWeights();

private:
    Ui::VehicleWeights *ui;
};

#endif // VEHICLEWEIGHTS_H
