//HANSER Florian
//BAUER Guillaume

#ifndef SIMULATION_H
#define SIMULATION_H

#include <QMainWindow>
#include "enums.h"

namespace Ui {
class Simulation;
}

class Simulation : public QMainWindow
{
    Q_OBJECT

public:
    explicit Simulation(QWidget *parent = 0);
    ~Simulation();

signals:
    void valveState(Side,State);
    void gateState(Side,State,int);

public slots:
    void emergencyStop();
    void endEmergencyStop();
    void openValve(Side);
    void closeValve(Side);
    void openGate(Side);
    void closeGate(Side);
    void stopGate(Side);
    void setRedLight(Side);
    void setGreenLight(Side);

private:
    Ui::Simulation *ui;
};

#endif // SIMULATION_H
