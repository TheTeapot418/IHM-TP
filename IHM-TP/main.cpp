//HANSER Florian
//BAUER Guillaume

#include "interface.h"
#include "blackbox.h"
#include "simulation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Interface i;
    BlackBox bb;
    Simulation s;
    i.show();
    s.show();

    return a.exec();
}
