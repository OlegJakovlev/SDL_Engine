#pragma once

#include "../AbstractComponent.h"
#include "../../Logger/PhysicsLogger/PhysicsLogger.h"
#include "../../Physics/Vector2.h"

class PhysicsComponent : public AbstractComponent
{
public:
    ~PhysicsComponent();

    void LoadConfig(const nlohmann::json& config) override;
    void Update() override;

    void AdjustVelocityXComponent(int deltaXSpeed);
    void AdjustVelocityYComponent(int deltaYSpeed);

    void AddCollisionResponseEvent(const std::function<void()>& function);
private:
    void Move(const Vector2::Vector2<int>& movementVector);
    void CheckCollisionsRecursively(GameObject::GameObject* collisionCheckWith);
    bool AABBOverlap(GameObject::GameObject* checkOverlapWith);
    float SweptAABB(GameObject::GameObject* secondBody);

    Vector2::Vector2<int> velocity;
    Vector2::Vector2<float> normal;

    bool isTrigger;
    std::vector<std::function<void()>> collisionResponseEvents;
};

