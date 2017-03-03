//HANSER Florian
//BAUER Guillaume

#include "simulation.h"

Simulation::Simulation()
{
    components.push_back(&usValve);
    components.push_back(&dsValve);
    components.push_back(&usGate);
    components.push_back(&dsGate);
    components.push_back(&usLight);
    components.push_back(&dsLight);

    window.show();
}

void Simulation::emergencyStop() {

}

void Simulation::endEmergencyStop() {

}

void Simulation::openValve(Side v) {

}

void Simulation::closeValve(Side v) {

}

void Simulation::openGate(Side g) {

}

void Simulation::closeGate(Side g) {

}

void Simulation::stopGate(Side g) {

}

void Simulation::setRedLight(Side l) {

}

void Simulation::setGreenLight(Side l) {

}
