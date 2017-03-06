//HANSER Florian
//BAUER Guillaume

#include "blackbox.h"
#include "ui_interface.h"

#include <iostream>
#include <unistd.h>
using namespace std;

BlackBox::BlackBox(Interface * i,Simulation * s,QObject *parent) : QObject(parent) {
    upGate = downGate = CLOSED;
    upValve = downValve = OPEN;
    emergency = false;
    isOperating = false;
    goingTo = UPSTREAM;
    connection(i,s);
}

void BlackBox::connection(Interface * i,Simulation * s){

    //Connects between BlackBox and Interface
    QObject::connect(i->getUi()->enterButton,SIGNAL(clicked()),this,SLOT(enter()));
    QObject::connect(i->getUi()->exitButton,SIGNAL(clicked()),this,SLOT(exit()));
    QObject::connect(i->getUi()->switchMode,SIGNAL(sliderMoved(int)),this,SLOT(switchMode(int)));

    QObject::connect(i->getUi()->upOpenGateButton,SIGNAL(clicked()),this,SLOT(upGateOpen()));
    QObject::connect(i->getUi()->upCloseGateButton,SIGNAL(clicked()),this,SLOT(upGateClose()));
    QObject::connect(i->getUi()->upStopGateButton,SIGNAL(clicked()),this,SLOT(upGateStop()));
    QObject::connect(i->getUi()->upOpenValveButton,SIGNAL(clicked()),this,SLOT(upValveOpen()));
    QObject::connect(i->getUi()->upCloseValveButton,SIGNAL(clicked()),this,SLOT(upValveClose()));
    QObject::connect(i->getUi()->upGreenLightButton,SIGNAL(clicked()),this,SLOT(upGreenLight()));
    QObject::connect(i->getUi()->upRedLightButton,SIGNAL(clicked()),this,SLOT(upRedLight()));

    QObject::connect(i->getUi()->downOpenGateButton,SIGNAL(clicked()),this,SLOT(downGateOpen()));
    QObject::connect(i->getUi()->downCloseGateButton,SIGNAL(clicked()),this,SLOT(downGateClose()));
    QObject::connect(i->getUi()->downStopGateButton,SIGNAL(clicked()),this,SLOT(downGateStop()));
    QObject::connect(i->getUi()->downOpenValveButton,SIGNAL(clicked()),this,SLOT(downValveOpen()));
    QObject::connect(i->getUi()->downCloseValveButton,SIGNAL(clicked()),this,SLOT(downValveClose()));
    QObject::connect(i->getUi()->downGreenLightButton,SIGNAL(clicked()),this,SLOT(downGreenLight()));
    QObject::connect(i->getUi()->downRedLightButton,SIGNAL(clicked()),this,SLOT(downRedLight()));

    QObject::connect(i->getUi()->emergencyButton,SIGNAL(clicked()),this,SLOT(emergencyButton()));
    QObject::connect(i->getUi()->stopEmergencyButton,SIGNAL(clicked()),this,SLOT(endEmergencyButton()));
    QObject::connect(i->getUi()->loginButton,SIGNAL(clicked()),i,SLOT(login()));
    QObject::connect(i->getUi()->logoutButton,SIGNAL(clicked()),i,SLOT(logout()));

    QObject::connect(this,SIGNAL(upGateUpdate(State,int)),i,SLOT(upGateUpdate(State,int)));
    QObject::connect(this,SIGNAL(upValveUpdate(State)),i,SLOT(upValveUpdate(State)));
    QObject::connect(this,SIGNAL(upLightUpdate(State)),i,SLOT(upLightUpdate(State)));
    QObject::connect(this,SIGNAL(downGateUpdate(State,int)),i,SLOT(downGateUpdate(State,int)));
    QObject::connect(this,SIGNAL(downValveUpdate(State)),i,SLOT(downValveUpdate(State)));
    QObject::connect(this,SIGNAL(downLightUpdate(State)),i,SLOT(downLightUpdate(State)));

    //Connects between BlackBox and Simulation
    QObject::connect(this,SIGNAL(emergencyStop()),s,SLOT(emergencyStop()));
    QObject::connect(this,SIGNAL(endEmergencyStop()),s,SLOT(endEmergencyStop()));
    QObject::connect(this,SIGNAL(openValve(Side)),s,SLOT(openValve(Side)));
    QObject::connect(this,SIGNAL(closeValve(Side)),s,SLOT(closeValve(Side)));
    QObject::connect(this,SIGNAL(openGate(Side)),s,SLOT(openGate(Side)));
    QObject::connect(this,SIGNAL(closeGate(Side)),s,SLOT(closeGate(Side)));
    QObject::connect(this,SIGNAL(stopGate(Side)),s,SLOT(stopGate(Side)));
    QObject::connect(this,SIGNAL(setRedLight(Side)),s,SLOT(setRedLight(Side)));
    QObject::connect(this,SIGNAL(setGreenLight(Side)),s,SLOT(setGreenLight(Side)));

    QObject::connect(s,SIGNAL(valveState(Side,State)),this,SLOT(valveState(Side,State)));
    QObject::connect(s,SIGNAL(gateState(Side,State,int)),this,SLOT(gateState(Side,State,int)));

}

////////////////////
//      SLOT      //
////////////////////

//from simulation
void BlackBox::valveState(Side v,State s){
    switch(v){
        case UPSTREAM :
            upValve = s;
            emit upValveUpdate(s);
            break;
        case DOWNSTREAM :
            downValve = s;
            emit downValveUpdate(s);
            break;
    }
}

void BlackBox::gateState(Side v,State s,int i){
    if(s != ALERT){
        if(i == 100)
            s = OPEN;
        else if(i == 0)
            s = CLOSED;
    }
    switch(v){
        case UPSTREAM :
            upGate = s;
            emit upGateUpdate(s,i);
            break;
        case DOWNSTREAM :
            downGate = s;
            emit downGateUpdate(s,i);
            break;
    }
}


//from interface
void BlackBox::emergencyButton(){
    if(emergency)return;
    emit emergencyStop();
    emergency = true;
    emit upLightUpdate(CLOSED);
    emit downLightUpdate(CLOSED);
}


//automatic mode
void BlackBox::switchMode(int i){
    if(i == 0)
        goingTo = UPSTREAM;
    else
        goingTo = DOWNSTREAM;
}

void BlackBox::upOpen(){
    if(upGate == OPEN){
        emit setGreenLight(UPSTREAM);
        emit upLightUpdate(OPEN);
        return;
    }
    emit setRedLight(DOWNSTREAM);
    emit downLightUpdate(CLOSED);
    if(downGate != CLOSED){
        emit closeGate(DOWNSTREAM);
        //Sleep ?
    }
    if(downValve == OPEN)
        emit closeValve(DOWNSTREAM);
    if(upValve == CLOSED)
        emit openValve(UPSTREAM);
    emit openGate(UPSTREAM);
    //Sleep
    emit setGreenLight(UPSTREAM);
    emit upLightUpdate(OPEN);

}

void BlackBox::downOpen(){
    if(downGate == OPEN){
        emit setGreenLight(DOWNSTREAM);
        emit downLightUpdate(OPEN);
        return;
    }
    emit setRedLight(UPSTREAM);
    emit upLightUpdate(CLOSED);
    if(upGate != CLOSED){
        emit closeGate(UPSTREAM);
        //Sleep ?
    }
    if(upValve == OPEN)
        emit closeValve(UPSTREAM);
    if(downValve == CLOSED)
        emit openValve(DOWNSTREAM);
    emit openGate(DOWNSTREAM);
    //sleep
    emit setGreenLight(DOWNSTREAM);
    emit downLightUpdate(OPEN);
}

//mutex !!!!!

void BlackBox::enter(){
    if(emergency || isOperating)return;
    isOperating = true;
    cout << goingTo << endl;
    if(goingTo == UPSTREAM)
        downOpen();
    else
        upOpen();
    isOperating = false;
}

void BlackBox::exit(){
    if(emergency || isOperating)return;
    isOperating = true;
    if(goingTo == UPSTREAM)
        upOpen();
    else
        downOpen();
    isOperating = false;
}


//manual mode
void BlackBox::upGateOpen(){
    if(emergency)return;
    if((upGate == CLOSED || upGate == STOPPED) && upValve == OPEN && downValve == CLOSED)
        emit openGate(UPSTREAM);
}

void BlackBox::upGateClose(){
    if(emergency)return;
    if(upGate != CLOSED)
        emit closeGate(UPSTREAM);
}

void BlackBox::upGateStop(){
    if(emergency)return;
    if(upGate == OPENING || upGate == CLOSING)
        emit stopGate(UPSTREAM);
}

void BlackBox::upValveOpen(){
    if(emergency)return;
    if(upValve == CLOSED && downGate == CLOSED)
        emit openValve(UPSTREAM);
}

void BlackBox::upValveClose(){
    if(emergency)return;
    if(upValve == OPEN)
    emit closeValve(UPSTREAM);
}

void BlackBox::upGreenLight(){
    if(emergency)return;
    if(upGate == OPEN){
        emit setGreenLight(UPSTREAM);
        emit upLightUpdate(OPEN);
    }
}

void BlackBox::upRedLight(){
    if(emergency)return;
    emit setRedLight(UPSTREAM);
    emit upLightUpdate(CLOSED);
}


void BlackBox::downGateOpen(){
    if(emergency)return;
    if((downGate == CLOSED || downGate == STOPPED) && upValve == CLOSED && downValve == OPEN)
        emit openGate(DOWNSTREAM);
}

void BlackBox::downGateClose(){
    if(emergency)return;
    if(downGate != CLOSED)
        emit closeGate(DOWNSTREAM);
}

void BlackBox::downGateStop(){
    if(emergency)return;
    if(downGate == OPENING || downGate == CLOSING)
        emit stopGate(DOWNSTREAM);
}

void BlackBox::downValveOpen(){
    if(emergency)return;
    if(downValve == CLOSED && upGate == CLOSED)
        emit openValve(DOWNSTREAM);
}

void BlackBox::downValveClose(){
    if(emergency)return;
    if(downValve == OPEN)
        emit closeValve(DOWNSTREAM);
}

void BlackBox::downGreenLight(){
    if(emergency)return;
    if(downGate == OPEN){
        emit setGreenLight(DOWNSTREAM);
        emit downLightUpdate(OPEN);
    }
}

void BlackBox::downRedLight(){
    if(emergency)return;
    emit setRedLight(DOWNSTREAM);
    emit downLightUpdate(CLOSED);
}


void BlackBox::endEmergencyButton(){
    if(!emergency)return;
    emit endEmergencyStop();
    emergency = false;
}
