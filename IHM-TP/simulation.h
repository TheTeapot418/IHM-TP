//HANSER Florian
//BAUER Guillaume

#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>

class Simulation : public QObject
{
    Q_OBJECT
public:
    explicit Simulation(QObject *parent = 0);

signals:

public slots:
    void emergencyStop(void);
    void endEmergencyStop(void);
    void openValve(int);
    void closeValve(int);
    void openGate(int);
    void closeGate(int);
    void stopGate(int);
    void setRedLight(int);
    void setGreenLight(int);
};

#endif // SIMULATION_H
