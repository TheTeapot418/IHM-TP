#ifndef LIGHT_H
#define LIGHT_H

#include <QPaintEvent>
#include "sluicecomponent.h"

class Light : public SluiceComponent
{
public:
    Light();

    void emergencyStop(void);
    void endEmergencyStop(void);
    void paint(QPaintEvent *);

    void setToRed(void);
    void setToGreen(void);

private:
    enum Color {
        RED,
        GREEN
    };

    Color color;
};

#endif // LIGHT_H
