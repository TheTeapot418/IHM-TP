#include "sluicecomponent.h"
#include <ctime>

SluiceComponent::SluiceComponent() {
    std::srand(std::time(NULL));
}

double SluiceComponent::rand_double() {
    return (double) std::rand() / (double) RAND_MAX;
}

bool SluiceComponent::randomFailure() {
    double rnd = rand_double();
    return (rnd <= failureProbability);
}
