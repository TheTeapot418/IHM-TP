#include <QPaintEvent>
#include "valve.h"
#include "enums.h"

Valve::Valve()
{

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

void Valve::paint(QPaintEvent* e) {

}

void Valve::open(void) {
    if (emergency) return;
    state = OPEN;
}

void Valve::close(void) {
    if (emergency) return;
    state = CLOSED;
}

State Valve::getState(void) {
    return state;
}
