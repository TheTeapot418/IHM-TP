//BAUER Guillaume
//HANSER Florian
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QPainter>
#include <QPixmap>
#include "paintable.h"


//Arrière plan de la simulation
class Background : public Paintable
{
public:
    Background();
    void paint(QPainter*);

private:
    QPixmap img;
};

#endif // BACKGROUND_H
