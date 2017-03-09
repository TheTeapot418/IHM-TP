//BAUER Guillaume
//HANSER Florian
#include <QPainter>
#include "background.h"

//Le constructeur charge l'image à rendre
Background::Background()
{
    img = QPixmap(":/resources/Background.png");
}

//Rendu de l'image dans la fenêtre
void Background::paint(QPainter* p) {
    p->drawPixmap(0, 0, img);
}
