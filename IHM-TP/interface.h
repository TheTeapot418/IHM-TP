//HANSER Florian
//BAUER Guillaume

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include "enums.h"

namespace Ui {
class Interface;
}

//MainWindows
class Interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = 0);
    ~Interface();

    //Getteur de l'ui
    Ui::Interface *getUi();

    //Fonction qui ferme l'application à l'appui de bouton de fermeture
    void closeEvent(QCloseEvent*);

private:
    Ui::Interface *ui;

public slots:
    //Slot qui update les valeurs(couleurs , avancement)
    void upGateUpdate(State,int);
    void upValveUpdate(State);
    void upLightUpdate(State);

    void downGateUpdate(State,int);
    void downValveUpdate(State);
    void downLightUpdate(State);


};

#endif // INTERFACE_H
