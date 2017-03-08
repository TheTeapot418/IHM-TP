//HANSER Florian
//BAUER Guillaume

#ifndef BLACKBOX_H
#define BLACKBOX_H

#include <QObject>
#include "enums.h"
#include "simulation.h"
#include "interface.h"

using namespace std;

//La BlackBox permet la communication entre la simulation et l'interface
class BlackBox : public QObject
{
    Q_OBJECT
public:
    explicit BlackBox(Interface * i,Simulation * s,QObject *parent = 0);

private:
    //Attributs
    Side goingTo = UPSTREAM;
    State upGate = CLOSED,downGate = CLOSED;
    State upValve = OPEN,downValve = OPEN;
    Level water = MID;
    bool emergency = false;

    //Methodes
    void connection(Interface * i,Simulation * s);
    void emitLightSignal(Side,State);
    State gateState(Side);
    State valveState(Side);
    Interface * interface;

    //Exclusion mutuelle
    mutex mtx;
    enum {
        NONE,
        VERIFYGATE,
        CLOSINGGATE,
        VERIFYVALVE,
        WAITINGWATER,
        OPENGATE
    } operation = NONE;    //Etats de l'operation manuelle en cours
    Side operationSide;

signals:
    //Signaux émis à la simulation
    void emergencyStop();
    void endEmergencyStop();
    void openValve(Side);
    void closeValve(Side);
    void openGate(Side);
    void closeGate(Side);
    void stopGate(Side);
    void setRedLight(Side);
    void setGreenLight(Side);

    //Signaux émis à l'interface
    void upGateUpdate(State,int);
    void upValveUpdate(State);
    void upLightUpdate(State);
    void downGateUpdate(State,int);
    void downValveUpdate(State);
    void downLightUpdate(State);

    //Signals interne
    void openGateInternalSignal();

public slots:
    //Signaux reçus de la simulation
    void valveState(Side,State);
    void gateState(Side,State,int);
    void waterLevel(Level);

    //Signaux reçus de l'interface
    void login();
    void logout();
    void emergencyButton();
    void endEmergencyButton();
        //mode manuelle
        void switchMode(int);
        void enter();
        void exit();
        //mode automatique
        void upGateOpen();
        void upGateClose();
        void upGateStop();
        void upValveOpen();
        void upValveClose();
        void upGreenLight();
        void upRedLight();
        void downGateOpen();
        void downGateClose();
        void downGateStop();
        void downValveOpen();
        void downValveClose();
        void downGreenLight();
        void downRedLight();

    //Slot interne
    void openGateInternal();

};

#endif // BLACKBOX_H
