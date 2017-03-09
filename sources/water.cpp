//HANSER Florian
//BAUER Guillaume

#include "water.h"
#include "enums.h"

using namespace std;

//Le constructeur charge la ressource
Water::Water(){
    img = QPixmap(":/resources/WaterLevel.png");
}

//Rendu de l'eau dans la fenêtre
void Water::paint(QPainter* p) {
    p->drawPixmap(0, position,img);
}

//Setteur des états des vannes
//Si ALERT -> CLOSED
//Lance le thread de calcul de position s'il n'est pas déjà lancé
void Water::updateValve(Side s,State st) {
    mtx.lock();
    if(s == UPSTREAM)
        upValve = st==ALERT?CLOSED:st;
    else
        downValve = st==ALERT?CLOSED:st;
    mtx.unlock();
    mtx2.lock();
    if(!isRunning){
        isRunning = true;
        thread = std::thread(&Water::run, this);
        thread.detach();
    }
    mtx2.unlock();
}

//Calcul de la vitesse
// 0 si aucun mouvement à faire
#define MIN(A,B) A<B?A:B
#define ISNEG(X) X<0?0:X
void Water::calculVitesse(){
    mtx.lock();
    if(upValve == CLOSED && downValve == CLOSED){
        vitesse = 0;
    }else if(upValve == OPEN && downValve == CLOSED){
        if(position - debitMax < 0)
            vitesse = -position;
        else
            vitesse = -debitMax;
    }else if(upValve == CLOSED && downValve == OPEN){
        if(position + debitMax > positionMax)
            vitesse = positionMax-position;
        else
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

//Fonction du thread
//calcul la vitesse + niveau
//emet un signal à simulation de changement de position
//recommence après 100ms
void Water::run(){
    while(true) {

        calculVitesse();
        if(vitesse == 0)break;
        mtx.lock();
        position += vitesse;
        if(position == 0)
            level = HIGH;
        else if(position == positionMax)
            level = LOW;
        else
            level = MID;

        mtx.unlock();
        emit waterLevelInternal(level);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    mtx2.lock();
    isRunning = false;
    mtx2.unlock();
}
