#include <QWidget>
#include "simulationwindow.h"

SimulationWindow::SimulationWindow() : QWidget(0)
{
    setFixedSize(600, 600);
    setWindowTitle("Simulation");
    move(50, 50);
}

void SimulationWindow::paintEvent(QPaintEvent *) {

}
