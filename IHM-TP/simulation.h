//HANSER Florian
//BAUER Guillaume

#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <vector>
#include "enums.h"
#include "simulationwindow.h"
#include "sluicecomponent.h"
#include "valve.h"
#include "gate.h"
#include "light.h"


class Simulation : public QObject
{
    Q_OBJECT

public:
    explicit Simulation();

private:
    SimulationWindow window;

    Valve usValve;
    Valve dsValve;
    Gate usGate;
    Gate dsGate;
    Light usLight;
    Light dsLight;

    std::vector<SluiceComponent*> components;

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

    void usGateStateInternal(State, int);
    void dsGateStateInternal(State, int);
};

#endif // SIMULATION_H
