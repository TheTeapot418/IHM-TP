#include <QPainter>
#include <QPixmap>
#include <QString>
#include <string>
#include "valve.h"
#include "enums.h"

Valve::Valve()
{

}

Valve::Valve(QString oi, QString ci,QString ai) {
    openImg = QPixmap(oi);
    closedImg = QPixmap(ci);
    alarmImg = QPixmap(ai);
}

void Valve::emergencyStop(void) {
    if (emergency) return;
    state = ALERT;
    emergency = true;
}

void Valve::endEmergencyStop(void) {
    if (!emergency) return;
    state = CLOSED;
    emergency = false;
}

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

void Valve::open(void) {
    if (emergency) return;
    if (randomFailure()) {
        emergencyStop();
        return;
    }
    state = OPEN;
}

void Valve::close(void) {
    if (emergency) return;
    if (randomFailure()) {
        emergencyStop();
        return;
    }
    state = CLOSED;
}

State Valve::getState(void) {
    return state;
}
