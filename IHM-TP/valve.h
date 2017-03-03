#ifndef VALVE_H
#define VALVE_H

#include <QPaintEvent>
#include "sluicecomponent.h"
#include "enums.h"

class Valve : public SluiceComponent
{
public:
    Valve();
    void emergencyStop(void);
    void endEmergencyStop(void);
    void paint(QPaintEvent *);

    void open(void);
    void close(void);

    State getState(void);

private:
    State state = CLOSED;
    bool emergency = false;
};

#endif // VALVE_H
