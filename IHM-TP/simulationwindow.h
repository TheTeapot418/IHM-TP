#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QWidget>
#include <QPaintEvent>
#include <QCloseEvent>
#include <vector>
#include "paintable.h"

class SimulationWindow : public QWidget
{
public:
    SimulationWindow();
    SimulationWindow(std::vector<Paintable*>);
    ~SimulationWindow();

    void paintEvent(QPaintEvent*);

private:
    std::vector<Paintable*> entities;
};

#endif // SIMULATIONWINDOW_H
