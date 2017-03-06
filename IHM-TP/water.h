#ifndef WATER_H
#define WATER_H

#include <QPainter>
#include <QPixmap>
#include "paintable.h"
#include "enums.h"


class Water : public Paintable
{
public:
    Water();
    void paint(QPainter*);

    void setLevel(Level);


private:
    QPixmap midImg;
    QPixmap highImg;


    Level level = MID;
};

#endif // WATER_H
