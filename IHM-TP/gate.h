#ifndef GATE_H
#define GATE_H

#include <QPainter>
#include <QPixmap>
#include <Qstring>
#include <thread>
#include <mutex>

#include "sluicecomponent.h"
#include "enums.h"

class Gate : public QObject, public SluiceComponent
{
    Q_OBJECT

signals:
    void gateStateInternal(State, int);

public:
    Gate();
    Gate(QString,QString);

    void emergencyStop(void);
    void endEmergencyStop(void);
    void paint(QPainter*);

    void open(void);
    void close(void);
    void stop(void);

    State getState(void);
    int getPreciseState(void);

private:
    State state = CLOSED;
    int preciseState = 0;

    bool emergency = false;

    std::thread thread;
    bool threadRunning = false;

    void threadFunc(State);
    bool shouldDie = false;
    std::mutex mtx;
    std::mutex mtx2;

    QPixmap img;
    QPixmap imgAlarm;

    int seed;
    double rand_double(void);
    bool randomFailure(void);
};

#endif // GATE_H
