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
    cout << "BB : j'ai reçus un signal traité par valveState" << endln;
}

void BlackBox::gateState(Side g,State s,int i){
    cout << "BB : j'ai reçus un siganl traité par gateState" << endln;
}


//from interface
void BlackBox::emergencyButton(){
    cout << "BB : j'ai reçus un siganl traité par emergencyButton" << endln;
}


//automatic mode
void BlackBox::switchMode(int i){
    cout << "BB : j'ai reçus un siganl traité par switchMode" << endln;
}

void BlackBox::enter(){
    cout << "BB : j'ai reçus un siganl traité par enter" << endln;
}

void BlackBox::exit(){
    cout << "BB : j'ai reçus un siganl traité par exit" << endln;
}


void BlackBox::loginIn(){
    cout << "BB : j'ai reçus un siganl traité par loginIn" << endln;
}


//manual mode
void BlackBox::upGateOpen(){
    cout << "BB : j'ai reçus un siganl traité par upGateOpen" << endln;
}

void BlackBox::upGateClose(){
    cout << "BB : j'ai reçus un siganl traité par upGateClose" << endln;
}

void BlackBox::upGateStop(){
    cout << "BB : j'ai reçus un siganl traité par upGateStop" << endln;
}

void BlackBox::upValveOpen(){
    cout << "BB : j'ai reçus un siganl traité par upValveOpen" << endln;
}

void BlackBox::upValveClose(){
    cout << "BB : j'ai reçus un siganl traité par upValveClose" << endln;
}

void BlackBox::upGreenLigth(){
    cout << "BB : j'ai reçus un siganl traité par upGreenLigth" << endln;
}


void BlackBox::downGateOpen(){
    cout << "BB : j'ai reçus un siganl traité par downGateOpen" << endln;
}

void BlackBox::downGateClose(){
    cout << "BB : j'ai reçus un siganl traité par downGateClose" << endln;
}

void BlackBox::downGateStop(){
    cout << "BB : j'ai reçus un siganl traité par downGateStop" << endln;
}

void BlackBox::downValveOpen(){
    cout << "BB : j'ai reçus un siganl traité par downValveOpen" << endln;
}

void BlackBox::downValveClose(){
    cout << "BB : j'ai reçus un siganl traité par downValveClose" << endln;
}

void BlackBox::downGreenLigth(){
    cout << "BB : j'ai reçus un siganl traité par downGreenLigth" << endln;
}


void BlackBox::endEmergencyButton(){
    cout << "BB : j'ai reçus un siganl traité par endEmergencyButton" << endln;
}

void BlackBox::logOut(){
    cout << "BB : j'ai reçus un siganl traité par logOut" << endln;
}
