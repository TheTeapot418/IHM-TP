#ifndef SLUICECOMPONENT_H
#define SLUICECOMPONENT_H

#include "paintable.h"

class SluiceComponent : public Paintable
{
public:
    virtual void emergencyStop(void) = 0;
    virtual void endEmergencyStop(void) = 0;

protected:
    double rand_double(void);
    bool randomFailure(void);

    double failureProbability = .1;
};

#endif // SLUICECOMPONENT_H
