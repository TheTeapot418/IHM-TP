//HANSER Florian
//BAUER Guillaume

#include "interface.h"
#include "ui_interface.h"
#include "blackbox.h"
#include "simulation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Interface i;
    BlackBox bb;
    Simulation s;
    i.show();

    //Exemple de connection entre les objet (surtout pour recup le ui)
    QObject::connect(i.getUi()->enterButton,SIGNAL(clicked()),&bb,SLOT(enter()));
    QObject::connect(i.getUi()->exitButton,SIGNAL(clicked()),&bb,SLOT(exit()));
    QObject::connect(i.getUi()->switchMode,SIGNAL(sliderMoved(int)),&bb,SLOT(switchMode(int)));

    QObject::connect(i.getUi()->upOpenGateButton,SIGNAL(clicked()),&bb,SLOT(upGateOpen()));
    QObject::connect(i.getUi()->upCloseGateButton,SIGNAL(clicked()),&bb,SLOT(upGateClose()));
    QObject::connect(i.getUi()->upStopGateButton,SIGNAL(clicked()),&bb,SLOT(upGateStop()));
    QObject::connect(i.getUi()->upOpenValveButton,SIGNAL(clicked()),&bb,SLOT(upValveOpen()));
    QObject::connect(i.getUi()->upCloseValveButton,SIGNAL(clicked()),&bb,SLOT(upValveClose()));
    QObject::connect(i.getUi()->upGreenLightButton,SIGNAL(clicked()),&bb,SLOT(upGreenLight()));
    QObject::connect(i.getUi()->upRedLightButton,SIGNAL(clicked()),&bb,SLOT(upRedLight()));

    QObject::connect(i.getUi()->downOpenGateButton,SIGNAL(clicked()),&bb,SLOT(downGateOpen()));
    QObject::connect(i.getUi()->downCloseGateButton,SIGNAL(clicked()),&bb,SLOT(downGateClose()));
    QObject::connect(i.getUi()->downStopGateButton,SIGNAL(clicked()),&bb,SLOT(downGateStop()));
    QObject::connect(i.getUi()->downOpenValveButton,SIGNAL(clicked()),&bb,SLOT(downValveOpen()));
    QObject::connect(i.getUi()->downCloseValveButton,SIGNAL(clicked()),&bb,SLOT(downValveClose()));
    QObject::connect(i.getUi()->downGreenLightButton,SIGNAL(clicked()),&bb,SLOT(downGreenLight()));
    QObject::connect(i.getUi()->downRedLightButton,SIGNAL(clicked()),&bb,SLOT(downRedLight()));

    QObject::connect(i.getUi()->emergencyButton,SIGNAL(clicked()),&bb,SLOT(emergencyButton()));
    QObject::connect(i.getUi()->stopEmergencyButton,SIGNAL(clicked()),&bb,SLOT(endEmergencyButton()));
    QObject::connect(i.getUi()->loginButton,SIGNAL(clicked()),&i,SLOT(login()));
    QObject::connect(i.getUi()->logoutButton,SIGNAL(clicked()),&i,SLOT(logout()));

    QObject::connect(&bb,SIGNAL(upGateUpdate(State,int)),&i,SLOT(upGateUpdate(State,int)));
    QObject::connect(&bb,SIGNAL(upValveUpdate(State)),&i,SLOT(upValveUpdate(State)));
    QObject::connect(&bb,SIGNAL(upLightUpdate(State)),&i,SLOT(upLightUpdate(State)));
    QObject::connect(&bb,SIGNAL(downGateUpdate(State,int)),&i,SLOT(downGateUpdate(State,int)));
    QObject::connect(&bb,SIGNAL(downValveUpdate(State)),&i,SLOT(downValveUpdate(State)));
    QObject::connect(&bb,SIGNAL(downLightUpdate(State)),&i,SLOT(downLightUpdate(State)));

    //Connects between BLackBox and Simulation
    QObject::connect(&bb, SIGNAL(emergencyStop()), &s, SLOT(emergencyStop()));
    QObject::connect(&bb, SIGNAL(endEmergencyStop()), &s, SLOT(endEmergencyStop()));
    QObject::connect(&bb, SIGNAL(openValve(Side)), &s, SLOT(openValve(Side)));
    QObject::connect(&bb, SIGNAL(closeValve(Side)), &s, SLOT(closeValve(Side)));
    QObject::connect(&bb, SIGNAL(openGate(Side)), &s, SLOT(openGate(Side)));
    QObject::connect(&bb, SIGNAL(closeGate(Side)), &s, SLOT(closeGate(Side)));
    QObject::connect(&bb, SIGNAL(stopGate(Side)), &s, SLOT(stopGate(Side)));
    QObject::connect(&bb, SIGNAL(setRedLight(Side)), &s, SLOT(setRedLight(Side)));
    QObject::connect(&bb, SIGNAL(setGreenLight(Side)), &s, SLOT(setGreenLight(Side)));

    QObject::connect(&s, SIGNAL(valveState(Side,State)), &bb, SLOT(valveState(Side,State)));
    QObject::connect(&s, SIGNAL(gateState(Side,State,int)), &bb, SLOT(gateState(Side,State,int)));

    //bb.test();
    return a.exec();
}
