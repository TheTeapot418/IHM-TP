#include <QPaintEvent>
#include "valve.h"
#include "enums.h"

Valve::Valve()
{

}

void Valve::emergencyStop(void) {
    state = CLOSED;
    emergency = true;
}

void Valve::endEmergencyStop(void) {
    emergency = false;
}

void Valve::paint(QPaintEvent *) {

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
