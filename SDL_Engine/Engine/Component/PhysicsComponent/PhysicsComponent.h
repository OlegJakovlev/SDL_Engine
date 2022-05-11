#pragma once

#include "../AbstractComponent.h"
#include "../../Logger/PhysicsLogger/PhysicsLogger.h"
#include "../../Physics/Vector2.h"

class PhysicsComponent : public AbstractComponent
{
public:
    ~PhysicsComponent();

    void Update() override;

    void Move(const Vector2::Vector2<int>& movementVector);

    bool AABBOverlap(GameObject::GameObject* checkOverlapWith);
    float SweptAABB(GameObject::GameObject* secondBody);

private:
    void CheckCollisionsRecursively(GameObject::GameObject* collisionCheckWith);

    Vector2::Vector2<int> velocity;
    Vector2::Vector2<float> normal;
};

