//BAUER Guillaume
//HANSER Florian
#ifndef GATE_H
#define GATE_H

#include <QPainter>
#include <QPixmap>
#include <QString>
#include <thread>
#include <mutex>

#include "sluicecomponent.h"
#include "enums.h"

//Porte de l'écluse
class Gate : public QObject, public SluiceComponent
{
    Q_OBJECT

signals:
    //Signal transmettant l'état de la porte à la simulation
    void gateStateInternal(State, int);

public:
    Gate();
    //Le constructeur prend en paramètres les chemins vers les ressources à dessiner dans
    //la fenêtre
    Gate(QString,QString);

    //Fonctions de gestion de l'arrêt d'urgence
    void emergencyStop(void);
    void endEmergencyStop(void);

    //Rendu dans la fenêtre
    void paint(QPainter*);

    //Contrôles de la porte
    void open(void);
    void close(void);
    void stop(void);

    //Getters
    State getState(void);
    int getPreciseState(void);

private:
    //Etat général
    State state = CLOSED;
    //Etat précis (% d'ouverture/fermeture)
    int preciseState = 0;

    //est en état d'urgence
    bool emergency = false;

    //Thread actionnant la porte
    std::thread thread;
    bool threadRunning = false;

    void threadFunc(State);
    bool shouldDie = false;
    std::mutex mtx;
    std::mutex mtx2;

    //Ressources à renre dans la fenêtre
    QPixmap img;
    QPixmap imgAlarm;

    //Generation de pannes aléatoires
    double rand_double(void);
    bool randomFailure(void);
};

#endif // GATE_H
