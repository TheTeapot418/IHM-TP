#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QWidget>
#include <QPaintEvent>

class SimulationWindow : public QWidget
{
public:
    SimulationWindow();

    paintEvent(QPaintEvent*);
};

#endif // SIMULATIONWINDOW_H
