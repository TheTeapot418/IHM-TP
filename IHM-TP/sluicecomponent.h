#ifndef SLUICECOMPONENT_H
#define SLUICECOMPONENT_H

#include <QPaintEvent>

class SluiceComponent
{
public:
    virtual void emergencyStop(void) = 0;
    virtual void endEmergencyStop(void) = 0;
    virtual void paint(QPaintEvent*) = 0;
};

#endif // SLUICECOMPONENT_H
