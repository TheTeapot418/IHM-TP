#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QPainter>
#include <QPixmap>
#include "paintable.h"


class Background : public Paintable
{
public:
    Background();
    void paint(QPainter*);

private:
    QPixmap img;
};

#endif // BACKGROUND_H
