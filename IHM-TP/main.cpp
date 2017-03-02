//HANSER Florian
//BAUER Guillaume

#include "interface.h"
#include "ui_interface.h"       //utile pour le ui
#include "blackbox.h"
#include "simulation.h"
#include "ui_simulation.h"      //la meme
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Interface i;
    BlackBox bb;
    Simulation s;
    i.show();
    s.show();

    //Exemple de connection entre les objet (surtout pour recup le ui)
    QObject::connect(i.getUi()->enterButton,SIGNAL(clicked()),&bb,SLOT(enter()));

    return a.exec();
}
