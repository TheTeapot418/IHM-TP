#include "water.h"
#include "enums.h"

#include <iostream>
using namespace std;

//Water::Water(QObject *parent) : Paintable(),QObject(parent) {
Water::Water(){
    img = QPixmap(":/images/WaterLevel_High.png");
    upValve = downValve = OPEN;
    vitesse = 0;
    thread = std::thread(&Water::run,this);
    thread.detach();
}

//Water::~Water(){}

void Water::paint(QPainter* p) {
    p->drawPixmap(0, position,img);
}

void Water::updateValve(Side s,State st) {
    mtx.lock();
    if(s == UPSTREAM)
        upValve = st==ALERT?CLOSED:st;
    else
        downValve = st==ALERT?CLOSED:st;
    mtx.unlock();
}

#define MIN(A,B) A<B?A:B
void Water::calculVitesse(){
    mtx.lock();
    if(upValve == CLOSED && downValve == CLOSED){
        vitesse = 0;
    }else if(upValve == OPEN && downValve == CLOSED){
        vitesse = -debitMax;
    }else if(upValve == CLOSED && downValve == OPEN){
        vitesse = debitMax;
    }else{//deux vannes ouvertes
        if(position == positionMax/2)
            vitesse = 0;
        else if(position > positionMax/2)
            vitesse = -(MIN(debitMax/2,position-positionMax/2));
        else
            vitesse = MIN(debitMax/2,positionMax/2-position);
    }
    mtx.unlock();
}

void Water::run(){
    calculVitesse();
    mtx.lock();
    position += vitesse;
    if(position <= 0)
        position = 0;
    else if(position >= positionMax)
        position = positionMax;
    //cout << "position : "+position << endl;
    switch(position){
        case 0 :
            level = HIGH;
            break;
        case 448 :
            level = LOW;
            break;
        default :
            level = MID;
            break;
    }
    mtx.unlock();
    emit waterLevelInternal(level);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    run();
}
