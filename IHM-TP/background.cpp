#include <QPainter>
#include "background.h"

Background::Background()
{
    img = QPixmap(":/images/Background.png");
}

void Background::paint(QPainter* p) {
    p->drawPixmap(0, 0, img);
}
