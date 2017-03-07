#ifndef WATER_H
#define WATER_H

#include <QPainter>
#include <QPixmap>
#include <QObject>
#include <thread>
#include <mutex>

#include "paintable.h"
#include "enums.h"

class Water : public QObject,public Paintable
{
    Q_OBJECT

public:
    //explicit Water(QObject *parent = 0);
    Water();
    void paint(QPainter*);
    void updateValve(Side,State);

signals :
    void waterLevelInternal(Level);

private:
    QPixmap img;

    int debitMax = 4;
    int positionMax = 208;
    int position = 104;
    Level level = MID;

    std::mutex mtx;
    State upValve,downValve;
    int vitesse;
    void calculVitesse();

    std::thread thread;
    void run();
};

#endif // WATER_H
