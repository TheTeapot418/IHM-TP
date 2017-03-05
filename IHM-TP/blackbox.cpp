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
}

void BlackBox::gateState(Side g,State s,int i){
}


//from interface
void BlackBox::emergencyButton(){
    emit openGate(UPSTREAM);
}


//automatic mode
void BlackBox::switchMode(int i){
}

void BlackBox::enter(){
}

void BlackBox::exit(){
}


//manual mode
void BlackBox::upGateOpen(){
}

void BlackBox::upGateClose(){
}

void BlackBox::upGateStop(){
}

void BlackBox::upValveOpen(){
}

void BlackBox::upValveClose(){
}

void BlackBox::upGreenLight(){
}

void BlackBox::upRedLight(){
}


void BlackBox::downGateOpen(){
}

void BlackBox::downGateClose(){
}

void BlackBox::downGateStop(){
}

void BlackBox::downValveOpen(){
}

void BlackBox::downValveClose(){
}

void BlackBox::downGreenLight(){
}

void BlackBox::downRedLight(){
}


void BlackBox::endEmergencyButton(){
}

void BlackBox::test(){
    return;
}
