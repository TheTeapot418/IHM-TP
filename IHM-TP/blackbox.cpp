//HANSER Florian
//BAUER Guillaume

#include "blackbox.h"

#include <iostream>
#include <unistd.h>
using namespace std;

BlackBox::BlackBox(QObject *parent) : QObject(parent) {
    upGate = downGate = CLOSED;
    upValve = downValve = OPEN;
    emergency = false;
    isOperating = false;
    goingTo = UPSTREAM;
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
    emit emergencyStop();
    emergency = true;
    emit upLightUpdate(CLOSED);
    emit downLightUpdate(CLOSED);
}


//automatic mode
void BlackBox::switchMode(int i){
    cout << i << endl;
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
        sleep(11);
    }
    if(downValve == OPEN)
        emit closeValve(DOWNSTREAM);
    if(upValve == CLOSED)
        emit openValve(UPSTREAM);
    emit openGate(UPSTREAM);
    sleep(11);
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
    emit endEmergencyStop();
    emergency = false;
}
