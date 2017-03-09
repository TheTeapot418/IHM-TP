//BAUER Guillaume
//HANSER Florian
#ifndef LIGHT_H
#define LIGHT_H

#include <QPainter>
#include <QPixmap>
#include <QString>
#include "sluicecomponent.h"

//Feu
class Light : public SluiceComponent
{
public:
    Light();
    //Le constructeur prend en paramètre les chemins vers les ressourcesà rendre dans la fenêtre
    Light(QString, QString);

    //Gestion des arrêts d'urgence
    void emergencyStop(void);
    void endEmergencyStop(void);

    //Rendu dans la fenêtre
    void paint(QPainter*);

    //Contrôles du feu
    void setToRed(void);
    void setToGreen(void);

private:
    //Couleur du feu
    enum Color {
        RED,
        GREEN
    };

    //Couleur actuelle
    Color color = RED;

    //Est en état d'alerte
    bool emergency = false;

    //Ressources à rendre dans la fenêtre
    QPixmap redImg;
    QPixmap greenImg;
};

#endif // LIGHT_H
