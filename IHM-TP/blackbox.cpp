//HANSER Florian
//BAUER Guillaume

#include "blackbox.h"

#include <iostream>
using namespace std;

BlackBox::BlackBox(QObject *parent) : QObject(parent) {

}


////////////////////
//      SLOT      //
////////////////////

//from simulation
void BlackBox::valveState(Side v,State s){
    switch(v){
        case UPSTREAM :
            emit upValveUpdate(s);
            break;
        case DOWNSTREAM :
            emit downValveUpdate(s);
            break;
    }
}

void BlackBox::gateState(Side v,State s,int i){
    switch(v){
        case UPSTREAM :
            emit upGateUpdate(s,i);
            break;
        case DOWNSTREAM :
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
    emit openGate(UPSTREAM);
}

void BlackBox::upGateClose(){
    emit closeGate(UPSTREAM);
}

void BlackBox::upGateStop(){
    emit stopGate(UPSTREAM);
}

void BlackBox::upValveOpen(){
    emit openValve(UPSTREAM);
}

void BlackBox::upValveClose(){
    emit closeValve(UPSTREAM);
}

void BlackBox::upGreenLight(){
    emit setGreenLight(UPSTREAM);
    emit upLightUpdate(OPEN);
}

void BlackBox::upRedLight(){
    emit setRedLight(UPSTREAM);
    emit upLightUpdate(CLOSED);
}


void BlackBox::downGateOpen(){
    emit openGate(DOWNSTREAM);
}

void BlackBox::downGateClose(){
    emit closeGate(DOWNSTREAM);
}

void BlackBox::downGateStop(){
    emit stopGate(DOWNSTREAM);
}

void BlackBox::downValveOpen(){
    emit openValve(DOWNSTREAM);
}

void BlackBox::downValveClose(){
    emit closeValve(DOWNSTREAM);
}

void BlackBox::downGreenLight(){
    emit setGreenLight(DOWNSTREAM);
    emit downLightUpdate(OPEN);
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
