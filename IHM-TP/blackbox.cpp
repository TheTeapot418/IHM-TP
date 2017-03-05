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
    cout << "BB : j'ai reçus un signal traité par valveState" << endl;
}

void BlackBox::gateState(Side g,State s,int i){
    cout << "BB : j'ai reçus un siganl traité par gateState" << endl;
}


//from interface
void BlackBox::emergencyButton(){
    cout << "BB : j'ai reçus un siganl traité par emergencyButton" << endl;
}


//automatic mode
void BlackBox::switchMode(int i){
    cout << "BB : j'ai reçus un siganl traité par switchMode" << endl;
}

void BlackBox::enter(){
    cout << "BB : j'ai reçus un siganl traité par enter" << endl;
}

void BlackBox::exit(){
    cout << "BB : j'ai reçus un siganl traité par exit" << endl;
}


void BlackBox::logIn(){
    cout << "BB : j'ai reçus un siganl traité par logIn" << endl;
}


//manual mode
void BlackBox::upGateOpen(){
    cout << "BB : j'ai reçus un siganl traité par upGateOpen" << endl;
}

void BlackBox::upGateClose(){
    cout << "BB : j'ai reçus un siganl traité par upGateClose" << endl;
}

void BlackBox::upGateStop(){
    cout << "BB : j'ai reçus un siganl traité par upGateStop" << endl;
}

void BlackBox::upValveOpen(){
    cout << "BB : j'ai reçus un siganl traité par upValveOpen" << endl;
}

void BlackBox::upValveClose(){
    cout << "BB : j'ai reçus un siganl traité par upValveClose" << endl;
}

void BlackBox::upGreenLight(){
    cout << "BB : j'ai reçus un siganl traité par upGreenLight" << endl;
}

void BlackBox::upRedLight(){
    cout << "BB : j'ai reçus un siganl traité par upRedLight" << endl;
}


void BlackBox::downGateOpen(){
    cout << "BB : j'ai reçus un siganl traité par downGateOpen" << endl;
}

void BlackBox::downGateClose(){
    cout << "BB : j'ai reçus un siganl traité par downGateClose" << endl;
}

void BlackBox::downGateStop(){
    cout << "BB : j'ai reçus un siganl traité par downGateStop" << endl;
}

void BlackBox::downValveOpen(){
    cout << "BB : j'ai reçus un siganl traité par downValveOpen" << endl;
}

void BlackBox::downValveClose(){
    cout << "BB : j'ai reçus un siganl traité par downValveClose" << endl;
}

void BlackBox::downGreenLight(){
    cout << "BB : j'ai reçus un siganl traité par downGreenLight" << endl;
}

void BlackBox::downRedLight(){
    cout << "BB : j'ai reçus un siganl traité par downRedLight" << endl;
}


void BlackBox::endEmergencyButton(){
    cout << "BB : j'ai reçus un siganl traité par endEmergencyButton" << endl;
}

void BlackBox::logOut(){
    cout << "BB : j'ai reçus un siganl traité par logOut" << endl;
}

void BlackBox::test(){
    return;
}
