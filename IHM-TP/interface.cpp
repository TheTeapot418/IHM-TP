//HANSER Florian
//BAUER Guillaume

#include "interface.h"
#include "ui_interface.h"

Interface::Interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);
    ui->manualWidget->setVisible(false);
    ui->logoutButton->setVisible(false);
    ui->stopEmergencyButton->setVisible(false);
    ui->upGateLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->downGateLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    move(1100, 50);
}

Interface::~Interface()
{
    delete ui;
}

Ui::Interface * Interface::getUi(){
    return ui;
}

void Interface::closeEvent(QCloseEvent *event) {
    QApplication::quit();
}

void Interface::upGateUpdate(State st,int i){
    switch(st){
        case OPEN :
            ui->upGateLabel->setStyleSheet("background-color:green;");
            ui->upGateLabel->setText("");
            break;
        case OPENING :
            ui->upGateLabel->setStyleSheet("background-color:blue;color:white;");
            ui->upGateLabel->setText("Ouverture : "+QString::number(i)+"%");
            break;
        case CLOSING :
            ui->upGateLabel->setStyleSheet("background-color:blue;color:white;");
            ui->upGateLabel->setText("Fermeture : "+QString::number(i)+"%");
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
            ui->upGateLabel->setStyleSheet("background-color:blue;color:white;");
            ui->upGateLabel->setText("Arrêtée : "+QString::number(i)+"%");
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
    switch(st){
        case OPEN :
            ui->downGateLabel->setStyleSheet("background-color:green;");
            ui->downGateLabel->setText("");
            break;
        case OPENING :
            ui->downGateLabel->setStyleSheet("background-color:blue;color:white;");
            ui->downGateLabel->setText("Ouverture : "+QString::number(i)+"%");
            break;
        case CLOSING :
            ui->downGateLabel->setStyleSheet("background-color:blue;color:white;");
            ui->downGateLabel->setText("Fermeture : "+QString::number(i)+"%");
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
            ui->downGateLabel->setStyleSheet("background-color:blue;color:white;");
            ui->downGateLabel->setText("Arrêtée : "+QString::number(i)+"%");
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


