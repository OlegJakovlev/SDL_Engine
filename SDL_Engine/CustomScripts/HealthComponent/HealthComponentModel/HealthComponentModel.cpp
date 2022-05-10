#include "HealthComponentModel.h"

void HealthComponentModel::AddHealth(unsigned int points) {
    health += points;
}

void HealthComponentModel::SubstractHealth(unsigned int points) {
    health -= points;
}

unsigned int HealthComponentModel::GetHealth() const {
    return health;
}
