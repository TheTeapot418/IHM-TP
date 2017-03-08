//BAUER Guillaume
//HANSER Florian
#ifndef SLUICECOMPONENT_H
#define SLUICECOMPONENT_H

#include "paintable.h"

//Classe définissant un élément de l'écluse
class SluiceComponent : public Paintable
{
public:
    SluiceComponent();
    //Gestion des alertes
    virtual void emergencyStop(void) = 0;
    virtual void endEmergencyStop(void) = 0;

protected:
    //Fonctions de génrération d'erreur aléatoire
    double rand_double(void);
    bool randomFailure(void);

    double failureProbability = .001;
};

#endif // SLUICECOMPONENT_H
