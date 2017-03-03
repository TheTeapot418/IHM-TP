#ifndef GATE_H
#define GATE_H

#include <QPaintEvent>

#include "sluicecomponent.h"
#include "enums.h"

class Gate : public SluiceComponent
{
public:
    Gate();

    void emergencyStop(void);
    void endEmergencyStop(void);
    void paint(QPaintEvent*);

    void open(void);
    void close(void);
    void stop(void);

    State getState(void);
    int getPreciseState(void);

private:
    State state;
    int preciseState = 0;
};

#endif // GATE_H
