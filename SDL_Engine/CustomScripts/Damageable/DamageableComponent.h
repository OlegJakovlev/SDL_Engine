#pragma once

#ifndef DamageableComponent_H
#define DamageableComponent_H

#include "../../Engine/Component/AbstractComponent.h"

class DamageableComponent : public AbstractComponent {
public:
    void SetActive(bool newValue);
    bool IsActive() const;

private:
    bool isActive;
};

#endif