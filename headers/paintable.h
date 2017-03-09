//BAUER Guillaume
//HANSER Florian
#ifndef PAINTABLE_H
#define PAINTABLE_H

#include <QPainter>

//Classe abstraite définisssant un objet pouvant être dessiné dans une fenêtre
class Paintable
{
public:
    //Fonction de rendu
    virtual void paint(QPainter*) = 0;
};

#endif // PAINTABLE_H
