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

#include "background.h"

Simulation::Simulation()
{

    usValve = Valve(":/images/US_Valve_Open.png", ":/images/US_Valve_Closed.png");
    dsValve = Valve(":/images/DS_Valve_Open.png", ":/images/DS_Valve_Closed.png");

    usLight = Light(":/images/US_Light_Red.png", ":/images/US_Light_Green.png");
    dsLight = Light(":/images/DS_Light_Red.png", ":/images/DS_Light_Green.png");

    usGate = new Gate(":/images/US_Gate.png");
    dsGate = new Gate(":/images/DS_Gate.png");

    components.push_back(&usValve);
    components.push_back(&dsValve);
    components.push_back(usGate);
    components.push_back(dsGate);
    components.push_back(&usLight);
    components.push_back(&dsLight);

    connect(usGate, SIGNAL(gateStateInternal(State,int)), this, SLOT(usGateStateInternal(State,int)));
    connect(dsGate, SIGNAL(gateStateInternal(State,int)), this, SLOT(dsGateStateInternal(State,int)));

    std::vector<Paintable*> p;
    p.push_back(&background);
    p.insert(p.end(), components.begin(), components.end());

    window = new SimulationWindow(p);
    window->show();
}

Simulation::~Simulation() {
    window->~SimulationWindow();
    delete window;
    delete usGate;
    delete dsGate;
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
        usGate->open();
        break;
    case DOWNSTREAM:
        dsGate->open();
    }
}

void Simulation::closeGate(Side g) {
    switch(g) {
    case UPSTREAM:
        usGate->close();
        break;
    case DOWNSTREAM:
        dsGate->close();
    }
}

void Simulation::stopGate(Side g) {
    switch(g) {
    case UPSTREAM:
        usGate->stop();
        break;
    case DOWNSTREAM:
        dsGate->stop();
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
