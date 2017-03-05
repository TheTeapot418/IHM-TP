//HANSER Florian
//BAUER Guillaume

#include "blackbox.h"

#include <iostream>
using namespace std;

BlackBox::BlackBox(QObject *parent) : QObject(parent) {
    upGate = downGate = CLOSED;
    upValve = downValve = OPEN;
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
    emit emergencyStop();
}


//automatic mode
void BlackBox::switchMode(int i){
    cout << i << endl;
    if(i == 0)
        goingTo = UPSTREAM;
    else
        goingTo = DOWNSTREAM;
}

void BlackBox::enter(){
}

void BlackBox::exit(){
}


//manual mode
void BlackBox::upGateOpen(){
    if(upGate != OPEN && upValve == OPEN && downValve == CLOSED)
        emit openGate(UPSTREAM);
}

void BlackBox::upGateClose(){
    if(upGate != CLOSED)
        emit closeGate(UPSTREAM);
}

void BlackBox::upGateStop(){
    if(upGate == OPENING || upGate == CLOSING)
        emit stopGate(UPSTREAM);
}

void BlackBox::upValveOpen(){
    if(upValve == CLOSED)
        emit openValve(UPSTREAM);
}

void BlackBox::upValveClose(){
    if(upValve == OPEN)
    emit closeValve(UPSTREAM);
}

void BlackBox::upGreenLight(){
    if(upGate == OPEN){
        emit setGreenLight(UPSTREAM);
        emit upLightUpdate(OPEN);
    }
}

void BlackBox::upRedLight(){
    emit setRedLight(UPSTREAM);
    emit upLightUpdate(CLOSED);
}


void BlackBox::downGateOpen(){
    if(downGate != OPEN && upValve == CLOSED && downValve == OPEN)
        emit openGate(DOWNSTREAM);
}

void BlackBox::downGateClose(){
    if(downGate != CLOSED)
        emit closeGate(DOWNSTREAM);
}

void BlackBox::downGateStop(){
    if(downGate == OPENING || downGate == CLOSING)
        emit stopGate(DOWNSTREAM);
}

void BlackBox::downValveOpen(){
    if(downValve == CLOSED)
        emit openValve(DOWNSTREAM);
}

void BlackBox::downValveClose(){
    if(downValve == OPEN)
        emit closeValve(DOWNSTREAM);
}

void BlackBox::downGreenLight(){
    if(downGate == OPEN){
        emit setGreenLight(DOWNSTREAM);
        emit downLightUpdate(OPEN);
    }
}

void BlackBox::downRedLight(){
    emit setRedLight(DOWNSTREAM);
    emit downLightUpdate(CLOSED);
}


void BlackBox::endEmergencyButton(){
    emit endEmergencyStop();
}

void BlackBox::test(){
    return;
}
