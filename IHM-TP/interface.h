//HANSER Florian
//BAUER Guillaume

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include "enums.h"

namespace Ui {
class Interface;
}

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = 0);
    ~Interface();
    Ui::Interface *getUi();

private:
    Ui::Interface *ui;

};

#endif // INTERFACE_H
