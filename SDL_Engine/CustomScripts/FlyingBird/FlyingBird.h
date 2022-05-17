#pragma once

#ifndef FlyingBird_H
#define FlyingBird_H

#include "../../Engine/Component/AbstractComponent.h"
#include "../../Engine/Component/PhysicsComponent/PhysicsComponent.h"
#include "../../Engine/Component/AnimationComponent/AnimationComponent.h"

class FlyingBird : public AbstractComponent {
public:
    void Init() override;

private:
    PhysicsComponent* physics;
    AnimationComponent* animator;

    const int MAX_SPEED_X = 6;
    const int MAX_SPEED_Y = 3;
};

#endif