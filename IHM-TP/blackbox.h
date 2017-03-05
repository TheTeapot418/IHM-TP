//HANSER Florian
//BAUER Guillaume

#ifndef BLACKBOX_H
#define BLACKBOX_H

#include <QObject>
#include "enums.h"

class BlackBox : public QObject
{
    Q_OBJECT
public:
    explicit BlackBox(QObject *parent = 0);
    void test();

private:
    Side goingTo;

signals:
    //to simulation
    void emergencyStop();
    void endEmergencyStop();
    void openValve(Side);
    void closeValve(Side);
    void openGate(Side);
    void closeGate(Side);
    void stopGate(Side);
    void setRedLight(Side);
    void setGreenLight(Side);

    //to interface
    void upGateUpdate(State,int);
    void upValveUpdate(State);
    void upLightUpdate(State);

    void downGateUpdate(State,int);
    void downValveUpdate(State);
    void downLightUpdate(State);

public slots:
    //from simulation
    void valveState(Side,State);
    void gateState(Side,State,int); //int pour la progression

    //from interface
    void emergencyButton();

        //automatic mode
        void switchMode(int);
        void enter();
        void exit();


            //manual mode
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

        void endEmergencyButton();

};

#endif // BLACKBOX_H
