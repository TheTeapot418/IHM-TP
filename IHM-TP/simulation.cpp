//HANSER Florian
//BAUER Guillaume

#include <vector>
#include "simulation.h"
#include "enums.h"
#include "simulationwindow.h"
#include "sluicecomponent.h"
#include "valve.h"
#include "gate.h"
#include "light.h"

Simulation::Simulation()
{
    components.push_back(&usValve);
    components.push_back(&dsValve);
    components.push_back(&usGate);
    components.push_back(&dsGate);
    components.push_back(&usLight);
    components.push_back(&dsLight);

    connect((Gate*)&usGate, SIGNAL(gateStateInternal(Side,State,int)), this, SLOT(gateStateInternal(Side,State,int)));
    connect((Gate*)&dsGate, SIGNAL(gateStateInternal(Side,State,int)), this, SLOT(gateStateInternal(Side,State,int)));

    window.show();
}

void Simulation::emergencyStop() {

}

void Simulation::endEmergencyStop() {

}

void Simulation::openValve(Side v) {
    State s;

    switch (v) {
    case UPSTREAM:
        usValve.open();
        s = usValve.getState();
        break;
    case DOWNSTREAM:
        dsValve.open();
        s = dsValve.getState();
    }

    emit(valveState(v, s));
}

void Simulation::closeValve(Side v) {
    State s;

    switch (v) {
    case UPSTREAM:
        usValve.close();
        s = usValve.getState();
        break;
    case DOWNSTREAM:
        dsValve.close();
        s = dsValve.getState();
    }

    emit(valveState(v, s));
}

void Simulation::openGate(Side g) {

}

void Simulation::closeGate(Side g) {

}

void Simulation::stopGate(Side g) {

}

void Simulation::setRedLight(Side l) {
    switch (l) {
    case UPSTREAM:
        usLight.setToRed();
        break;
    case DOWNSTREAM:
        dsLight.setToRed();
    }
}

void Simulation::setGreenLight(Side l) {
    switch (l) {
    case UPSTREAM:
        usLight.setToGreen();
        break;
    case DOWNSTREAM:
        dsLight.setToGreen();
    }
}

void Simulation::gateStateInternal(Side side, State state, int ps) {

}
