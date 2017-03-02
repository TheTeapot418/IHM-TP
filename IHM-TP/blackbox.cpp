//HANSER Florian
//BAUER Guillaume

#include "blackbox.h"

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

void BlackBox::lightState(Side l,State s){

}

void BlackBox::waterState(){

}


//from interface
void BlackBox::emergencyButton(){

}


//automatic mode
void BlackBox::switchMode(int i){

}

void BlackBox::enter(){

}

void BlackBox::exit(){

}


void BlackBox::loginIn(){

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

void BlackBox::upGreenLigth(){

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

void BlackBox::downGreenLigth(){

}


void BlackBox::endEmergencyButton(){

}

void BlackBox::logOut(){

}
