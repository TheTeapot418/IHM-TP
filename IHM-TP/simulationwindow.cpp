#include <QWidget>
#include <QPainter>
#include <vector>
#include "simulationwindow.h"
#include "paintable.h"

SimulationWindow::SimulationWindow(std::vector<Paintable*> e) : QWidget(0), entities(e)
{
    setFixedSize(600, 600);
    setWindowTitle("Simulation");
    move(50, 50);
}

void SimulationWindow::paintEvent(QPaintEvent* e) {
    QPainter painter;
    painter.begin(this);

    for (Paintable* p : entities) {
        p->paint(&painter);
    }

    QWidget::paintEvent(e);
    painter.end();
}
