//HANSER Florian
//BAUER Guillaume

#include "interface.h"
#include "ui_interface.h"       //utile pour le ui
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

    //Connects between BLackBox and Simulation
    QObject::connect(&bb, SIGNAL(emergencyStop()), &s, SLOT(emergencyStop()));
    QObject::connect(&bb, SIGNAL(endEmergencyStop()), &s, SLOT(endEmergencyStop()));
    QObject::connect(&bb, SIGNAL(openValve(Side)), &s, SLOT(openValve(Side)));
    QObject::connect(&bb, SIGNAL(closeValve(Side)), &s, SLOT(closeValve(Side)));
    QObject::connect(&bb, SIGNAL(openGate(Side)), &s, SLOT(closeGate(Side)));
    QObject::connect(&bb, SIGNAL(closeGate(Side)), &s, SLOT(closeGate(Side)));
    QObject::connect(&bb, SIGNAL(stopGate(Side)), &s, SLOT(stopGate(Side)));
    QObject::connect(&bb, SIGNAL(setRedLight(Side)), &s, SLOT(setRedLight(Side)));
    QObject::connect(&bb, SIGNAL(setGreenLight(Side)), &s, SLOT(setGreenLight(Side)));

    QObject::connect(&s, SIGNAL(valveState(Side,State)), &bb, SLOT(valveState(Side,State)));
    QObject::connect(&s, SIGNAL(gateState(Side,State,int)), &bb, SLOT(gateState(Side,State,int)));

    return a.exec();
}
