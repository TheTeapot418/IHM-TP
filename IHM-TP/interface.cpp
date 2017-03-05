//HANSER Florian
//BAUER Guillaume

#include "interface.h"
#include "ui_interface.h"
#include <iostream>
using namespace std;

Interface::Interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);
}

Interface::~Interface()
{
    delete ui;
}

Ui::Interface * Interface::getUi(){
    return ui;
}

void Interface::upGateUpdate(State st,int i){
    cout << "jai recu un signal" <<endl;
    QString txt;
    switch(st){
        case OPEN :
            ui->upGateLabel->setStyleSheet("background-color:green;");
            ui->upGateLabel->setText("");
            break;
        case OPENING :
            ui->upGateLabel->setStyleSheet("background-color:blue;");
            txt = "Opening : ";
            txt += QString::number(i);
            txt += "%";
            ui->upGateLabel->setText(txt);
            break;
        case CLOSING :
            ui->upGateLabel->setStyleSheet("background-color:blue;");
            txt = "Closing : ";
            txt += QString::number(i);
            txt += "%";
            ui->upGateLabel->setText(txt);
            break;
        case CLOSED :
            ui->upGateLabel->setStyleSheet("background-color:red;");
            ui->upGateLabel->setText("");
            break;
        case ALERT :
            ui->upGateLabel->setStyleSheet("background-color:orange;");
            ui->upGateLabel->setText("");
            break;
        case STOPPED :
            ui->upGateLabel->setStyleSheet("background-color:blue;");
            txt = "Stoped : ";
            txt += QString::number(i);
            txt += "%";
            ui->upGateLabel->setText(txt);
            break;
    }
}

void Interface::upValveUpdate(State st){
    switch(st){
        case OPEN :
            ui->upValveLabel->setStyleSheet("background-color:green;");
            break;
        case CLOSED :
            ui->upValveLabel->setStyleSheet("background-color:red;");
            break;
        case ALERT :
            ui->upValveLabel->setStyleSheet("background-color:orange;");
            break;
        default :
            break;
    }
}

void Interface::upLightUpdate(State st){
    switch(st){
        case OPEN :
            ui->upLightLabel->setStyleSheet("background-color:green;");
            break;
        case CLOSED :
            ui->upLightLabel->setStyleSheet("background-color:red;");
            break;
        default :
            break;
    }
}

void Interface::downGateUpdate(State st,int i){
    QString txt;
    switch(st){
        case OPEN :
            ui->downGateLabel->setStyleSheet("background-color:green;");
            ui->downGateLabel->setText("");
            break;
        case OPENING :
            ui->downGateLabel->setStyleSheet("background-color:blue;");
            txt = "Opening : ";
            txt += QString::number(i);
            txt += "%";
            ui->downGateLabel->setText(txt);
            break;
        case CLOSING :
            ui->downGateLabel->setStyleSheet("background-color:blue;");
            txt = "Closing : ";
            txt += QString::number(i);
            txt += "%";
            ui->downGateLabel->setText(txt);
            break;
        case CLOSED :
            ui->downGateLabel->setStyleSheet("background-color:red;");
            ui->downGateLabel->setText("");
            break;
        case ALERT :
            ui->downGateLabel->setStyleSheet("background-color:orange;");
            ui->downGateLabel->setText("");
            break;
        case STOPPED :
            ui->downGateLabel->setStyleSheet("background-color:blue;");
            txt = "Stoped : ";
            txt += QString::number(i);
            txt += "%";
            ui->downGateLabel->setText(txt);
            break;
    }
}

void Interface::downValveUpdate(State st){
    switch(st){
        case OPEN :
            ui->downValveLabel->setStyleSheet("background-color:green;");
            break;
        case CLOSED :
            ui->downValveLabel->setStyleSheet("background-color:red;");
            break;
        case ALERT :
            ui->downValveLabel->setStyleSheet("background-color:orange;");
            break;
        default :
            break;
    }
}

void Interface::downLightUpdate(State st){
    switch(st){
        case OPEN :
            ui->downLightLabel->setStyleSheet("background-color:green;");
            break;
        case CLOSED :
            ui->downLightLabel->setStyleSheet("background-color:red;");
            break;
        default :
            break;
    }
}

