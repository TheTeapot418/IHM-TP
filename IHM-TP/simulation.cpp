//HANSER Florian
//BAUER Guillaume

#include "simulation.h"
#include "ui_simulation.h"

Simulation::Simulation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Simulation)
{
    ui->setupUi(this);
}

Simulation::~Simulation()
{
    delete ui;
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
