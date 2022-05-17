#pragma once

#ifndef BombComponent_H
#define BombComponent_H

#include "../../Engine/Component/AbstractComponent.h"
#include "../../Engine/Component/AnimationComponent/AnimationComponent.h"

class ObjectPoolComponent;

class BombComponent : public AbstractComponent {
public:
    void Init() override;
    void Explode();

private:
    ObjectPoolComponent* explosionPool;
};

#endif