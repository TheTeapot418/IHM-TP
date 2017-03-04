#ifndef LIGHT_H
#define LIGHT_H

#include <QPainter>
#include "sluicecomponent.h"

class Light : public SluiceComponent
{
public:
    Light();

    void emergencyStop(void);
    void endEmergencyStop(void);
    void paint(QPainter*);

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
