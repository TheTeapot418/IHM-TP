//BAUER Guillaume
//HANSER Florian
#ifndef VALVE_H
#define VALVE_H

#include <QPainter>
#include <QPixmap>
#include <QString>
#include <string>
#include "sluicecomponent.h"
#include "enums.h"

//Vanne
class Valve : public SluiceComponent
{
public:
    Valve();
    //Le constructeur prend en paramètres les chemins vers les ressources à rendre dans la fenêtre
    Valve(QString, QString,QString);

    //Gestion des alarmes
    void emergencyStop(void);
    void endEmergencyStop(void);

    //Fonction de rendu
    void paint(QPainter*);

    //Commandes de la vanne
    void open(void);
    void close(void);

    //Getter
    State getState(void);

private:
    //Etat de la vanne
    State state = OPEN;

    //Est en état d'alerte
    bool emergency = false;

    //Resources à rendre
    QPixmap openImg;
    QPixmap closedImg;
    QPixmap alarmImg;
};

#endif // VALVE_H
