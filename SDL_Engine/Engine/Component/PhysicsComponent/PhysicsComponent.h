#pragma once

#include "../AbstractComponent.h"
#include "../../Logger/PhysicsLogger/PhysicsLogger.h"
#include "../../Physics/Vector2.h"

class PhysicsComponent : public AbstractComponent
{
public:
    ~PhysicsComponent();

    void Update() override;

    bool AABBOverlap(GameObject::GameObject* checkOverlapWith);
    float SweptAABB(GameObject::GameObject* secondBody);

private:
    Vector2::Vector2<float> velocity;
    Vector2::Vector2<float> normal;
};

