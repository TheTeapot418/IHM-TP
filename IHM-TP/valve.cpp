#include <QPainter>
#include <QPixmap>
#include <QString>
#include <string>
#include "valve.h"
#include "enums.h"

Valve::Valve()
{

}

Valve::Valve(QString oi, QString ci) {
    openImg = QPixmap(oi);
    closedImg = QPixmap(ci);
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
    default:
        p->drawPixmap(0, 0, closedImg);
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
