#include <QPainter>
#include <QPixmap>
#include <QString>
#include "light.h"

Light::Light()
{

}

Light::Light(QString ri, QString gi) {
    redImg = QPixmap(ri);
    greenImg = QPixmap(gi);
}

void Light::emergencyStop(void) {
    if (emergency) return;
    color = RED;
    emergency = true;
}

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

void Light::endEmergencyStop(void) {
    if (!emergency) return;
    emergency = false;
}

void Light::setToRed(void) {
    if (emergency) return;
    color = RED;
}

void Light::setToGreen(void) {
    if (emergency) return;
    color = RED;
}
