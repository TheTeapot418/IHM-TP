//HANSER Florian
//BAUER Guillaume

#include "blackbox.h"
#include "ui_interface.h"

#include <QInputDialog>

using namespace std;

BlackBox::BlackBox(Interface * i,Simulation * s,QObject *parent) : QObject(parent) {
    upGate = downGate = CLOSED;
    upValve = downValve = OPEN;
    emergency = false;
    operation = NONE;
    goingTo = UPSTREAM;
    connection(i,s);
    interface = i;
}

void BlackBox::connection(Interface * i,Simulation * s){

    //Connects between BlackBox and Interface
    connect(i->getUi()->enterButton,SIGNAL(clicked()),this,SLOT(enter()));
    connect(i->getUi()->exitButton,SIGNAL(clicked()),this,SLOT(exit()));
    connect(i->getUi()->switchMode,SIGNAL(sliderMoved(int)),this,SLOT(switchMode(int)));

    connect(i->getUi()->upOpenGateButton,SIGNAL(clicked()),this,SLOT(upGateOpen()));
    connect(i->getUi()->upCloseGateButton,SIGNAL(clicked()),this,SLOT(upGateClose()));
    connect(i->getUi()->upStopGateButton,SIGNAL(clicked()),this,SLOT(upGateStop()));
    connect(i->getUi()->upOpenValveButton,SIGNAL(clicked()),this,SLOT(upValveOpen()));
    connect(i->getUi()->upCloseValveButton,SIGNAL(clicked()),this,SLOT(upValveClose()));
    connect(i->getUi()->upGreenLightButton,SIGNAL(clicked()),this,SLOT(upGreenLight()));
    connect(i->getUi()->upRedLightButton,SIGNAL(clicked()),this,SLOT(upRedLight()));

    connect(i->getUi()->downOpenGateButton,SIGNAL(clicked()),this,SLOT(downGateOpen()));
    connect(i->getUi()->downCloseGateButton,SIGNAL(clicked()),this,SLOT(downGateClose()));
    connect(i->getUi()->downStopGateButton,SIGNAL(clicked()),this,SLOT(downGateStop()));
    connect(i->getUi()->downOpenValveButton,SIGNAL(clicked()),this,SLOT(downValveOpen()));
    connect(i->getUi()->downCloseValveButton,SIGNAL(clicked()),this,SLOT(downValveClose()));
    connect(i->getUi()->downGreenLightButton,SIGNAL(clicked()),this,SLOT(downGreenLight()));
    connect(i->getUi()->downRedLightButton,SIGNAL(clicked()),this,SLOT(downRedLight()));

    connect(i->getUi()->emergencyButton,SIGNAL(clicked()),this,SLOT(emergencyButton()));
    connect(i->getUi()->stopEmergencyButton,SIGNAL(clicked()),this,SLOT(endEmergencyButton()));
    connect(i->getUi()->loginButton,SIGNAL(clicked()),this,SLOT(login()));
    connect(i->getUi()->logoutButton,SIGNAL(clicked()),this,SLOT(logout()));

    connect(this,SIGNAL(upGateUpdate(State,int)),i,SLOT(upGateUpdate(State,int)));
    connect(this,SIGNAL(upValveUpdate(State)),i,SLOT(upValveUpdate(State)));
    connect(this,SIGNAL(upLightUpdate(State)),i,SLOT(upLightUpdate(State)));
    connect(this,SIGNAL(downGateUpdate(State,int)),i,SLOT(downGateUpdate(State,int)));
    connect(this,SIGNAL(downValveUpdate(State)),i,SLOT(downValveUpdate(State)));
    connect(this,SIGNAL(downLightUpdate(State)),i,SLOT(downLightUpdate(State)));

    //Connects between BlackBox and Simulation
    connect(this,SIGNAL(emergencyStop()),s,SLOT(emergencyStop()));
    connect(this,SIGNAL(endEmergencyStop()),s,SLOT(endEmergencyStop()));
    connect(this,SIGNAL(openValve(Side)),s,SLOT(openValve(Side)));
    connect(this,SIGNAL(closeValve(Side)),s,SLOT(closeValve(Side)));
    connect(this,SIGNAL(openGate(Side)),s,SLOT(openGate(Side)));
    connect(this,SIGNAL(closeGate(Side)),s,SLOT(closeGate(Side)));
    connect(this,SIGNAL(stopGate(Side)),s,SLOT(stopGate(Side)));
    connect(this,SIGNAL(setRedLight(Side)),s,SLOT(setRedLight(Side)));
    connect(this,SIGNAL(setGreenLight(Side)),s,SLOT(setGreenLight(Side)));

    connect(s,SIGNAL(valveState(Side,State)),this,SLOT(valveState(Side,State)));
    connect(s,SIGNAL(gateState(Side,State,int)),this,SLOT(gateState(Side,State,int)));
    connect(s,SIGNAL(waterLevel(Level)),this,SLOT(waterLevel(Level)));

    connect(this,SIGNAL(openGateInternalSignal()),this,SLOT(openGateInternal()),Qt::QueuedConnection);
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
        if(i == 100){
            s = OPEN;
            mtx.lock();
            if(operation == OPENGATE)
                emit openGateInternalSignal();
            mtx.unlock();

        }
        else if(i == 0){
            s = CLOSED;
            mtx.lock();
            if(operation == CLOSINGGATE)
                emit openGateInternalSignal();
            mtx.unlock();
        }
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

void BlackBox::waterLevel(Level lvl){
    if(lvl == HIGH || lvl == LOW){
        mtx.lock();
        if(operation == WAITINGWATER)
            emit openGateInternalSignal();
        mtx.unlock();
    }
    water = lvl;
}


//from interface
void BlackBox::login(){
    QString txt = QInputDialog::getText(interface,"Password ?","Mot de passe ?",QLineEdit::Password);
    if(txt == "password"){
        interface->getUi()->manualWidget->setVisible(true);
        interface->getUi()->logoutButton->setVisible(true);
        interface->getUi()->stopEmergencyButton->setVisible(true);

        interface->getUi()->automaticWidget->setVisible(false);
        interface->getUi()->loginButton->setVisible(false);

        mtx.lock();
        operation = NONE;
        mtx.unlock();
    }
}

void BlackBox::logout(){
    interface->getUi()->manualWidget->setVisible(false);
    interface->getUi()->logoutButton->setVisible(false);
    interface->getUi()->stopEmergencyButton->setVisible(false);

    interface->getUi()->automaticWidget->setVisible(true);
    interface->getUi()->loginButton->setVisible(true);
}

void BlackBox::emergencyButton(){
    if(emergency)return;
    emit emergencyStop();
    emergency = true;
    emit upLightUpdate(CLOSED);
    emit downLightUpdate(CLOSED);
    mtx.lock();
        operation = NONE;
    mtx.unlock();
}

void BlackBox::endEmergencyButton(){
    emit endEmergencyStop();
    emergency = false;
}



//automatic mode
void BlackBox::switchMode(int i){
    if(i == 0)
        goingTo = UPSTREAM;
    else
        goingTo = DOWNSTREAM;
}

void BlackBox::emitLightSignal(Side s,State st){
    if(s == UPSTREAM)
        emit upLightUpdate(st);
    else
        emit downLightUpdate(st);
}

State BlackBox::gateState(Side s){
    if(s == UPSTREAM)
        return upGate;
    else
        return downGate;
}

State BlackBox::valveState(Side s){
    if(s == UPSTREAM)
        return upValve;
    else
        return downValve;

}

#define OTHER(X) X==UPSTREAM?DOWNSTREAM:UPSTREAM
//#define SIDELEVEL(X) X==UPSTREAM?HIGH:LOW
void BlackBox::openGateInternal(){
    if(emergency)return;
    mtx.lock();
    switch(operation){
        case NONE : break;
        case VERIFYGATE :
            if(gateState(operationSide) == OPEN){
                emit setGreenLight(operationSide);
                emitLightSignal(operationSide,OPEN);
                operation = NONE;
                break;
            }
            operation = CLOSINGGATE;
        case CLOSINGGATE :
            if(gateState(OTHER(operationSide)) != CLOSED){
                emit setRedLight(OTHER(operationSide));
                emitLightSignal(OTHER(operationSide),CLOSED);
                emit closeGate(OTHER(operationSide));
                break;
            }
            operation = VERIFYVALVE;
        case VERIFYVALVE :
            if((operationSide==UPSTREAM)?(water != HIGH):(water != LOW)){
                if(valveState(OTHER(operationSide)) == OPEN)
                        emit closeValve(OTHER(operationSide));
                if(valveState(operationSide) == CLOSED)
                        emit openValve(operationSide);
            }
            operation = WAITINGWATER;
        case WAITINGWATER :
            if((operationSide==UPSTREAM)?(water != HIGH):(water != LOW))
                break;
            operation = OPENGATE;
        case OPENGATE :
            if(gateState(operationSide) != OPEN){
                emit openGate(operationSide);
            }else{
                emit setGreenLight(operationSide);
                emitLightSignal(operationSide,OPEN);
                operation = NONE;
            }
    }
    mtx.unlock();
}

//mutex !!!!!

void BlackBox::enter(){
    if(emergency)return;
    mtx.lock();
    if(operation == NONE){
        operation = VERIFYGATE;
        if(goingTo == UPSTREAM)
            operationSide = DOWNSTREAM;
        else
            operationSide = UPSTREAM;
        emit openGateInternalSignal();
    }
    mtx.unlock();
}

void BlackBox::exit(){
    if(emergency)return;
    mtx.lock();
    if(operation == NONE){
        operation = VERIFYGATE;
        operationSide = goingTo;
        emit openGateInternalSignal();
    }
    mtx.unlock();
}


//manual mode
void BlackBox::upGateOpen(){
    if(emergency)return;
    if((upGate == CLOSED || upGate == STOPPED) && water == HIGH)
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
    if((downGate == CLOSED || downGate == STOPPED) && water == LOW)
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


