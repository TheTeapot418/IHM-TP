//HANSER Florian
//BAUER Guillaume 

#ifndef WATER_H
#define WATER_H

#include <QPixmap>
#include <QObject>
#include <thread>
#include <mutex>

#include "paintable.h"
#include "enums.h"

//L'eau
class Water : public QObject,public Paintable
{
    Q_OBJECT

public:
    Water();
    void paint(QPainter*);

    //Setteur des états des vannes
    void updateValve(Side,State);

signals :
    //Signal transmettant le niveau de l'eau à la simulation
    void waterLevelInternal(Level);

private:
    //Resource
    QPixmap img;

    //Gestion des niveau et du debit
    int debitMax = 4;
    int positionMax = 208;
    int position = 104;
    Level level = MID;

    //Calcule la vitesse de l'animation
    void calculVitesse();

    //Exclusion mutuel n°1
    //position est aussi en zone critique
    std::mutex mtx;
    State upValve = OPEN,downValve = OPEN;
    int vitesse = 0;

    //Exclusion mutuel n°1
    std::mutex mtx2;
    bool isRunning;

    //Thread et la fonction lancé par thread
    std::thread thread;
    void run();
};

#endif // WATER_H
