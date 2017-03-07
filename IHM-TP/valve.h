#ifndef VALVE_H
#define VALVE_H

#include <QPainter>
#include <QPixmap>
#include <Qstring>
#include <string>
#include "sluicecomponent.h"
#include "enums.h"

class Valve : public SluiceComponent
{
public:
    Valve();
    Valve(QString, QString,QString);
    void emergencyStop(void);
    void endEmergencyStop(void);
    void paint(QPainter*);

    void open(void);
    void close(void);

    State getState(void);

private:
    State state = OPEN;
    bool emergency = false;

    QPixmap openImg;
    QPixmap closedImg;
    QPixmap alarmImg;
};

#endif // VALVE_H
