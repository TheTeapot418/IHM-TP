//BAUER Guillaume
//HANSER Florian
#include "sluicecomponent.h"
#include <ctime>

//Le constructeur initialise le générateur de nombres aléatoires
SluiceComponent::SluiceComponent() {
    std::srand(std::time(NULL));
}

//Génère un réel aléatoire
double SluiceComponent::rand_double() {
    return (double) std::rand() / (double) RAND_MAX;
}

//Génération aléatoire d'erreurs
bool SluiceComponent::randomFailure() {
    double rnd = rand_double();
    return (rnd <= failureProbability);
}

double SluiceComponent::getFP(){
    return failureProbability;
}
void SluiceComponent::setFP(double fp){
    failureProbability = fp;
}
