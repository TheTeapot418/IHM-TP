//BAUER Guillaume
//HANSER Florian
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <thread>
#include <chrono>
#include <ctime>
#include <random>
#include "gate.h"
#include "enums.h"

Gate::Gate()
{

}

//Le constructeur charge les ressources à rendre
Gate::Gate(QString gi,QString giAlarm) {
    img = QPixmap(gi);
    imgAlarm = QPixmap(giAlarm);
}

//Déclenche l'arrêt d'urgence de la porte
//Emmet un signal indiquant son état
void Gate::emergencyStop() {
    if (emergency) return;
    stop();
    emergency = true;
    state = ALERT;
    emit gateStateInternal(state, preciseState);
}

//Fin de l'état d'alerte
//En fin d'état d'alerte, la porte passe à l'état "arrêté"
void Gate::endEmergencyStop() {
    if (!emergency) return;
    emergency = false;
    state = STOPPED;
}

//Rendu de la porte dans la fenêtres aux coordonnées correspondant à sa position
void Gate::paint(QPainter* p) {
    int y = 0 - 2 * preciseState;
    p->drawPixmap(0, y, img);
    if(state == ALERT)
        p->drawPixmap(0,y,imgAlarm);
}

//Ouverture de la porte
//Si la porte n'est pas en train d'être actionnée, démarre le thread
//qui ouvre la porte en 10s
void Gate::open(void) {
    if (emergency) return;
    std::lock_guard<std::mutex> lock(mtx);
    if (threadRunning) return;
    mtx.unlock();
    shouldDie = false;
    state = OPENING;
    thread = std::thread(&Gate::threadFunc, this, OPEN);
    thread.detach();
}

//Fermeture de la porte
//Même chose que pour l'ouverture
void Gate::close(void) {
    if (emergency) return;
    std::lock_guard<std::mutex> lock(mtx);
    if (threadRunning) return;
    mtx.unlock();
    shouldDie = false;
    state = CLOSING;
    thread = std::thread(&Gate::threadFunc, this, CLOSED);
    thread.detach();
}

//Arrête de la porte
//Indique au thread de s'arrêter
void Gate::stop(void) {
    mtx2.lock();
    shouldDie = true;
    mtx2.unlock();
    state = STOPPED;
    emit gateStateInternal(state, preciseState);
}

//Getters
State Gate::getState(void) {
    return state;
}

int Gate::getPreciseState(void) {
    return preciseState;
}

//Thread d'ouverture/fermeture de la porte
void Gate::threadFunc(State target) {
    mtx.lock();
    threadRunning = true;
    mtx.unlock();

    //Ouverture de la porte
    if (target == OPEN) {
        for(; preciseState <= 100; preciseState += 1) {
            //Génération d'une erreur aléatoire
            if (randomFailure()) {
                threadRunning = false;
                emergencyStop();
                return;
            }
            //Signalement de l'état de la porte
            emit gateStateInternal(state, preciseState);
            //Attente passive
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::lock_guard<std::mutex> lock(mtx2);
            //Vérifie si le thread doit s'arrêter
            if (shouldDie) {
                mtx.lock();
                threadRunning = false;
                mtx.unlock();
                return;
            }
            mtx2.unlock();
        }
    //Fermeture de la porte
    } else if (target == CLOSED) {
        for(; preciseState >= 0; preciseState -= 1) {
            //Génération d'un erreur aléatoire
            if (randomFailure()) {
                threadRunning = false;
                emergencyStop();
                return;
            }
            //Signalement de l'état de la porte
            emit gateStateInternal(state, preciseState);
            //Attente passive
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::lock_guard<std::mutex> lock(mtx2);
            //Vérifie si le thread doit s'arrêter
            if (shouldDie) {
                mtx.lock();
                threadRunning = false;
                mtx.unlock();
                return;
            }
            mtx2.unlock();
        }
    }

    //Fin d'opération
    //Changement de l'état de la porte
    state = target;

    if (target == OPEN) {
        preciseState = 100;
    } else if (target == CLOSED) {
        preciseState = 0;
    }

    //Signalement de l'état de la porte
    emit gateStateInternal(state, preciseState);

    mtx.lock();
    threadRunning = false;
    mtx.unlock();
}


//Génération thread safe d'un réel aléatoire
double Gate::rand_double() {
    static thread_local std::mt19937 generator(std::time(NULL));
        std::uniform_real_distribution<double> distribution(0,1);
        return distribution(generator);
}

//Génération d'un erreur aléatoire
bool Gate::randomFailure() {
    double rnd = rand_double();
    return (rnd <= failureProbability);
}
