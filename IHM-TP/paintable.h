#ifndef PAINTABLE_H
#define PAINTABLE_H

#include <QPaintEvent>

class Paintable
{
public:
    virtual void paint(QPaintEvent*) = 0;
};

#endif // PAINTABLE_H
