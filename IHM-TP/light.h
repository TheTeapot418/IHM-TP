#ifndef LIGHT_H
#define LIGHT_H

#include <QPaintEvent>
#include "sluicecomponent.h"
#include "paintable.h"

class Light : public SluiceComponent, public Paintable
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

    Color color = RED;
    bool emergency = false;
};

#endif // LIGHT_H
