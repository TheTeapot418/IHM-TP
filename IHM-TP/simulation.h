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

#include "background.h"
#include "water.h"

//Classe principale de la simulation
class Simulation : public QObject
{
    Q_OBJECT

public:
    explicit Simulation();
    ~Simulation();

private:
    //Fenêtre de la simulation
    SimulationWindow* window;

    //Elements de l'écluse
    Valve usValve;
    Valve dsValve;
    Gate* usGate;
    Gate* dsGate;
    Light usLight;
    Light dsLight;

    //elements graphiques
    Background background;
    Water water;

    //Vecteur d'éléments des écluses
    std::vector<SluiceComponent*> components;

    //Déclenche un repaint de la fenêtre de simulation
    void requestWindowUpdate(void);

signals:
    //Signaux envoyés à l'interface
    void valveState(Side,State);
    void gateState(Side,State,int);
    void waterLevel(Level);

public slots:
    //Signaux reçus de l'interface
    void emergencyStop();
    void endEmergencyStop();
    void openValve(Side);
    void closeValve(Side);
    void openGate(Side);
    void closeGate(Side);
    void stopGate(Side);
    void setRedLight(Side);
    void setGreenLight(Side);

    //Signaux reçus des éléments de l'écluse
    void usGateStateInternal(State, int);
    void dsGateStateInternal(State, int);
    void waterLevelInternal(Level);

    //Signal du bouton d'option
    void optionClicked();
};

#endif // SIMULATION_H
