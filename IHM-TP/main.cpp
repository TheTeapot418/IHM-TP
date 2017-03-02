//HANSER Florian
//BAUER Guillaume

#include "mainwindow.h"
#include "blackbox.h"
#include "simulation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    BlackBox bb;
    w.show();

    return a.exec();
}
