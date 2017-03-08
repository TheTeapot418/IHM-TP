//BAUER Guillaume
//HANSER Florian
#include <QPainter>
#include <QPixmap>
#include <QString>
#include "light.h"

Light::Light()
{

}

//Le constructeur charge les ressources à rendre dans la fenêtre
Light::Light(QString ri, QString gi) {
    redImg = QPixmap(ri);
    greenImg = QPixmap(gi);
}

//Mise en état d'alerte du feu
//En état d'alerte, le feu passe au rouge
void Light::emergencyStop(void) {
    if (emergency) return;
    color = RED;
    emergency = true;
}

//Fin de l'état d'alerte
void Light::endEmergencyStop(void) {
    if (!emergency) return;
    emergency = false;
}

//Rendu dans la fenêtre
void Light::paint(QPainter* p) {
    switch (color) {
    case RED:
        p->drawPixmap(0, 0, redImg);
        break;
    case GREEN:
        p->drawPixmap(0, 0, greenImg);
        break;
    }
}

//Setters
void Light::setToRed(void) {
    if (emergency) return;
    color = RED;
}

void Light::setToGreen(void) {
    if (emergency) return;
    color = GREEN;
}
