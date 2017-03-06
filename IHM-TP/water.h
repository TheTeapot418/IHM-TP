#ifndef WATER_H
#define WATER_H

#include <QPainter>
#include <QPixmap>
#include "paintable.h"


class Water : public Paintable
{
public:
    Water();
    void paint(QPainter*);

    enum Level {
        LOW,
        MID,
        HIGH
    };

    void setLevel(Level);


private:
    QPixmap midImg;
    QPixmap highImg;


    Level level = MID;
};

#endif // WATER_H
