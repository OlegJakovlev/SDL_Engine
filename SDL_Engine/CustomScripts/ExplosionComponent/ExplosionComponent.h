#pragma once

#ifndef ExplosionComponent_H
#define ExplosionComponent_H

#include "../../Engine/Component/AbstractComponent.h"

class ExplosionComponent : public AbstractComponent {
public:
    void Init() override;
    void Update() override;

    void Explode();
};

#endif