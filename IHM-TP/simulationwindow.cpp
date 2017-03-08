//BAUER Guillaume
//HANSER Florian
#include <QWidget>
#include <QPainter>
#include <vector>
#include "simulationwindow.h"
#include "paintable.h"

SimulationWindow::SimulationWindow(std::vector<Paintable*> e) : QWidget(0), entities(e)
{
    //Définition et ouverture de la fenêtre
    setWindowFlags(Qt::WindowTitleHint);
    setFixedSize(1000, 600);
    setWindowTitle("Simulation");
    move(50, 50);
    setUpdatesEnabled(true);
}

//Fermeture de la fenêtre quand la mémoire est libérée
SimulationWindow::~SimulationWindow() {
    QWidget::close();
}

//Fonction de rendu
void SimulationWindow::paintEvent(QPaintEvent* e) {
    QPainter painter;
    painter.begin(this);

    //Itère à travers tous les objets pour les rendre
    for (Paintable* p : entities) {
        p->paint(&painter);
    }

    QWidget::paintEvent(e);
    painter.end();
}
