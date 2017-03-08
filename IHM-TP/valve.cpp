//BAUER Guillaume
//HANSER Florian
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <string>
#include "valve.h"
#include "enums.h"

Valve::Valve()
{

}

//Le constructeur charge les ressources à rendre
Valve::Valve(QString oi, QString ci,QString ai) {
    openImg = QPixmap(oi);
    closedImg = QPixmap(ci);
    alarmImg = QPixmap(ai);
}

//Arrêt d'urgence
void Valve::emergencyStop(void) {
    if (emergency) return;
    state = ALERT;
    emergency = true;
}

//Fin d'arrêt d'urgence
//Après un arrêt d'urgence, la vanne est fermée
void Valve::endEmergencyStop(void) {
    if (!emergency) return;
    state = CLOSED;
    emergency = false;
}

//Rendu dans la fenêtre
void Valve::paint(QPainter* p) {
    switch (state) {
    case OPEN:
        p->drawPixmap(0, 0, openImg);
        break;
    case CLOSED:
        p->drawPixmap(0, 0, closedImg);
        break;
    case ALERT :
        p->drawPixmap(0, 0, closedImg);
        p->drawPixmap(0, 0, alarmImg);
        break;
    default:
        break;
    }
}

//Ouverture de la vanne
void Valve::open(void) {
    if (emergency) return;
    if (randomFailure()) {
        emergencyStop();
        return;
    }
    state = OPEN;
}

//Fermeture de la vanne
void Valve::close(void) {
    if (emergency) return;
    if (randomFailure()) {
        emergencyStop();
        return;
    }
    state = CLOSED;
}

//Getter
State Valve::getState(void) {
    return state;
}
