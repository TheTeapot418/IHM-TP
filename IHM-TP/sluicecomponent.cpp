#include "sluicecomponent.h"
#include <ctime>

double SluiceComponent::rand_double() {
    return (double) std::rand() / (double) RAND_MAX;
}

bool SluiceComponent::randomFailure() {
    double rnd = rand_double();
    return (rnd <= rand_double());
}
