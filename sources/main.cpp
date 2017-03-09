//HANSER Florian
//BAUER Guillaume

#include "interface.h"
#include "blackbox.h"
#include "simulation.h"
#include "enums.h"
#include <QApplication>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Interface i;
    qRegisterMetaType<Level>("Level");
    Simulation s;
    BlackBox bb(&i,&s);
    std::srand(std::time(NULL));

    i.show();

    qRegisterMetaType<State>("State");
    return a.exec();
}
