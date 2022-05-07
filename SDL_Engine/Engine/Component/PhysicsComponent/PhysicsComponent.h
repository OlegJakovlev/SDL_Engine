#pragma once

#include "../AbstractComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../Logger/PhysicsLogger/PhysicsLogger.h"
#include "../../GameManager.h"

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

