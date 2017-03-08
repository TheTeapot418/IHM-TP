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

#include <iostream>
#include <QPushButton>
#include <QIcon>
#include <QString>
#include <QInputDialog>

//Clase principale de la simulation
Simulation::Simulation()
{

    //Instanciation des différents coposants de l'écluse
    usValve = Valve(":/images/US_Valve_Open.png", ":/images/US_Valve_Closed.png", ":/images/US_Valve_Alarm.png");
    dsValve = Valve(":/images/DS_Valve_Open.png", ":/images/DS_Valve_Closed.png", ":/images/DS_Valve_Alarm.png");

    usLight = Light(":/images/US_Light_Red.png", ":/images/US_Light_Green.png");
    dsLight = Light(":/images/DS_Light_Red.png", ":/images/DS_Light_Green.png");

    usGate = new Gate(":/images/US_Gate.png",":/images/US_Gate_Alarm.png");
    dsGate = new Gate(":/images/DS_Gate.png",":/images/DS_Gate_Alarm.png");

    //Création du tableau de composants
    components.push_back(&usValve);
    components.push_back(&dsValve);
    components.push_back(usGate);
    components.push_back(dsGate);
    components.push_back(&usLight);
    components.push_back(&dsLight);

    //Connexions internes à la simulation
    connect(usGate, SIGNAL(gateStateInternal(State,int)), this, SLOT(usGateStateInternal(State,int)));
    connect(dsGate, SIGNAL(gateStateInternal(State,int)), this, SLOT(dsGateStateInternal(State,int)));
    connect(&water,SIGNAL(waterLevelInternal(Level)),this,SLOT(waterLevelInternal(Level)));

    //Tableau d'éléments à rendre dans la fenêtre
    std::vector<Paintable*> p;
    p.push_back(&water);
    p.push_back(&background);
    p.insert(p.end(), components.begin(), components.end());


    //Création de la fenêtre
    window = new SimulationWindow(p);

    //Création du bouton de config
    QPushButton * optBt = new QPushButton(QIcon(":/images/option.png"),QString(""),window);
    optBt->setFixedSize(20,20);
    optBt->move(980,0);
    connect(optBt,SIGNAL(clicked()),this,SLOT(optionClicked()));

    window->show();
}

//Destructeur : on fait le ménage
Simulation::~Simulation() {
    delete usGate;
    delete dsGate;
}

//Arrêt d'urgence
void Simulation::emergencyStop() {
    //Déclenche l'arrêt d'urgence de tous les composants
    for (SluiceComponent* c : components) {
        c->emergencyStop();
    }

    //Signalement des nouveaux états à l'interface
    emit gateState(UPSTREAM, usGate->getState(), usGate->getPreciseState());
    emit gateState(DOWNSTREAM, dsGate->getState(), dsGate->getPreciseState());
    emit valveState(UPSTREAM, usValve.getState());
    emit valveState(DOWNSTREAM, dsValve.getState());
    water.updateValve(UPSTREAM,ALERT);
    water.updateValve(DOWNSTREAM,ALERT);

    //Mise à jour de la fenêtre
    requestWindowUpdate();
}

//Fin de l'état d'alerte
//Même chose qu'au dessus
void Simulation::endEmergencyStop() {
    for (SluiceComponent* c : components) {
        c->endEmergencyStop();
    }

    emit gateState(UPSTREAM, usGate->getState(), usGate->getPreciseState());
    emit gateState(DOWNSTREAM, dsGate->getState(), dsGate->getPreciseState());
    emit valveState(UPSTREAM, usValve.getState());
    emit valveState(DOWNSTREAM, dsValve.getState());

    requestWindowUpdate();
}

//Ouverture d'une vanne
void Simulation::openValve(Side v) {
    State s;

    //Ouverture de la valve correspondant à v
    switch (v) {
    case UPSTREAM:
        usValve.open();
        s = usValve.getState();
        break;
    case DOWNSTREAM:
        dsValve.open();
        s = dsValve.getState();
    }

    //signalement du changement d'état de la vanne
    emit(valveState(v, s));
    water.updateValve(v,s);

    //Mise à jour de la fenêtre
    requestWindowUpdate();
}

//Fermeture d'une vanne
//Même chose qu'au dessus
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
    water.updateValve(v,s);
    requestWindowUpdate();
}

//Ouverture d'une porte
void Simulation::openGate(Side g) {
    //Ouverture de la porte correspondant à g
    switch(g) {
    case UPSTREAM:
        usGate->open();
        break;
    case DOWNSTREAM:
        dsGate->open();
    }

    //Mise à jour de la fenêtre
    requestWindowUpdate();
}

//fermeture d'une porte
//Même chose qu'au dessus
void Simulation::closeGate(Side g) {
    switch(g) {
    case UPSTREAM:
        usGate->close();
        break;
    case DOWNSTREAM:
        dsGate->close();
    }
    requestWindowUpdate();
}

//Arrêt d'une porte
//Toujours la même chose
void Simulation::stopGate(Side g) {
    switch(g) {
    case UPSTREAM:
        usGate->stop();
        break;
    case DOWNSTREAM:
        dsGate->stop();
    }
    requestWindowUpdate();
}

//Commande de feu
//Passe le feu correspondant à l au rouge
void Simulation::setRedLight(Side l) {
    switch (l) {
    case UPSTREAM:
        usLight.setToRed();
        break;
    case DOWNSTREAM:
        dsLight.setToRed();
    }

    //Mise à jour de la fenêtre
    requestWindowUpdate();
}

//Commande de feu
//Passe le feu correspondant à l au vert
void Simulation::setGreenLight(Side l) {
    switch (l) {
    case UPSTREAM:
        usLight.setToGreen();
        break;
    case DOWNSTREAM:
        dsLight.setToGreen();
    }

    //Mise à jour de la fenêtre
    requestWindowUpdate();
}


//Slots internes à la simulation
//Mise à jour de l'état d'es portes
void Simulation::usGateStateInternal(State state, int ps) {
    emit gateState(UPSTREAM, state, ps);
    requestWindowUpdate();
}

void Simulation::dsGateStateInternal(State state, int ps) {
    emit gateState(DOWNSTREAM, state, ps);
    requestWindowUpdate();
}

//Etat de l'eau
void Simulation::waterLevelInternal(Level lvl){
    emit waterLevel(lvl);
    requestWindowUpdate();
}

//Mise à jour de la fenêtre
void Simulation::requestWindowUpdate() {
    window->repaint();
}

//Change les options
void Simulation::optionClicked(){
    bool ok;
    double val = QInputDialog::getDouble(window,"Option","Probabilité de panne :",usGate->getFP(),0,1,3,&ok);
    if(ok){
        usGate->setFP(val);
        dsGate->setFP(val);
        usValve.setFP(val);
        dsValve.setFP(val);
    }

}
