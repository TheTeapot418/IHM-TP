#include <QPaintEvent>
#include "light.h"

Light::Light()
{

}

void Light::emergencyStop(void) {
    if (emergency) return;
    color = RED;
    emergency = true;
}

void Light::endEmergencyStop(void) {
    if (!emergency) return;
    emergency = false;
}

void Light::paint(QPaintEvent *) {

}

void Light::setToRed(void) {
    if (emergency) return;
    color = RED;
}

void Light::setToGreen(void) {
    if (emergency) return;
    color = RED;
}
