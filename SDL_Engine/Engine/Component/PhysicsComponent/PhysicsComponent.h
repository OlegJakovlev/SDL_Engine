#pragma once

#include "../AbstractComponent.h"
#include "../../Logger/PhysicsLogger/PhysicsLogger.h"
#include "../../Physics/Vector2.h"
#include "../../../CustomScripts/PickableComponent/PickableComponent.h"

class PhysicsComponent : public AbstractComponent
{
public:
    ~PhysicsComponent();

    void LoadConfig(const nlohmann::json& config) override;
    void Update() override;

    void SetVelocity(Vector2::Vector2<int> newVelocity);
    void SetTeleportBehavior(bool newValue);
    void SetKinematic(bool newValue);
    void SetSliding(bool newValue);
    void SetMovable(bool newValue);

private:
    void Move(const Vector2::Vector2<int>& movementVector);
    void CheckCollisionsRecursively(GameObject::GameObject* collisionCheckWith);
    bool IsAabbCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

    Vector2::Vector2<int> velocity;
    Vector2::Vector2<float> movementDirection;

    bool isTrigger;
    bool isKinematic;
    bool isSliding;
    bool isMovable = false;
    bool teleportOnBoundaries = false;
};

