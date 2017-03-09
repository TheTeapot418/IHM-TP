//BAUER Guillaume
//HANSER Florian
#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QWidget>
#include <QPaintEvent>
#include <QCloseEvent>
#include <vector>
#include "paintable.h"

//Fenêtre de la simulation
class SimulationWindow : public QWidget
{
public:
    SimulationWindow();
    //Le constructeur prend en paramètre un vecteur d'objets à rendre dans la fenêtre
    SimulationWindow(std::vector<Paintable*>);
    ~SimulationWindow();

    //Evénement de repaint
    void paintEvent(QPaintEvent*);

private:
    //Objets à rendre
    std::vector<Paintable*> entities;
};

#endif // SIMULATIONWINDOW_H
