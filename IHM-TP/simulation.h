//HANSER Florian
//BAUER Guillaume

#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include "enums.h"
#include "simulationwindow.h"


class Simulation : public QObject
{
    Q_OBJECT

public:
    explicit Simulation();

private:
    SimulationWindow window;

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

};

#endif // SIMULATION_H
