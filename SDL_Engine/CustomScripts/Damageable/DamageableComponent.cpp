#include "DamageableComponent.h"

void DamageableComponent::SetActive(bool newValue) {
    isActive = newValue;
}

bool DamageableComponent::IsActive() const {
    return isActive;
}
