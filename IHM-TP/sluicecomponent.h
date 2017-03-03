#ifndef SLUICECOMPONENT_H
#define SLUICECOMPONENT_H

#include <QPaintEvent>

class SluiceComponent
{
public:
    virtual void emergencyStop(void);
    virtual void endEmergencyStop(void);
    virtual void paint(QPaintEvent*);
};

#endif // SLUICECOMPONENT_H
