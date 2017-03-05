//HANSER Florian
//BAUER Guillaume

#include <vector>
#include "simulation.h"
#include "enums.h"
#include "simulationwindow.h"
#include "sluicecomponent.h"
#include "paintable.h"
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

    connect(&usGate, SIGNAL(gateStateInternal(State,int)), this, SLOT(usGateStateInternal(State,int)));
    connect(&dsGate, SIGNAL(gateStateInternal(State,int)), this, SLOT(dsGateStateInternal(State,int)));

    std::vector<Paintable*> p(components.begin(), components.end());

    window = new SimulationWindow(p);
    window->show();
}

Simulation::~Simulation() {
    window->~SimulationWindow();
    delete window;
}

void Simulation::emergencyStop() {
    for (SluiceComponent* c : components) {
        c->emergencyStop();
    }
}

void Simulation::endEmergencyStop() {
    for (SluiceComponent* c : components) {
        c->endEmergencyStop();
    }
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
    switch(g) {
    case UPSTREAM:
        usGate.open();
        break;
    case DOWNSTREAM:
        dsGate.open();
    }
}

void Simulation::closeGate(Side g) {
    switch(g) {
    case UPSTREAM:
        usGate.close();
        break;
    case DOWNSTREAM:
        dsGate.close();
    }
}

void Simulation::stopGate(Side g) {
    switch(g) {
    case UPSTREAM:
        usGate.stop();
        break;
    case DOWNSTREAM:
        dsGate.stop();
    }
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

void Simulation::usGateStateInternal(State state, int ps) {
    emit gateState(UPSTREAM, state, ps);
}

void Simulation::dsGateStateInternal(State state, int ps) {
    emit gateState(DOWNSTREAM, state, ps);
}
