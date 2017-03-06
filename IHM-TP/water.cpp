#include <QPainter>
#include <QPixmap>
#include "water.h"
#include "enums.h"

Water::Water()
{
    midImg = QPixmap(":/images/WaterLevel_Mid.png");
    highImg = QPixmap(":/images/WaterLevel_High.png");
}

void Water::paint(QPainter* p) {
    switch (level) {
    case MID:
        p->drawPixmap(0, 0, midImg);
        break;
    case HIGH:
        p->drawPixmap(0, 0, highImg);
    default:
        break;
    }
}

void Water::setLevel(Level l) {
    level = l;
}
