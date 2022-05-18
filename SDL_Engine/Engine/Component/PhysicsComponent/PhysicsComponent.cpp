#include "PhysicsComponent.h"
#include "../../GameManager.h"

PhysicsComponent::~PhysicsComponent() {
}

void PhysicsComponent::LoadConfig(const nlohmann::json& config) {
    isTrigger = config.value("IsTrigger", false);
    isKinematic = config.value("IsKinematic", false);
    isSliding = config.value("IsSliding", false);
    isMovable = config.value("IsMovable", false);
}

void PhysicsComponent::Update() {
    movementDirection = Vector2::Vector2(velocity.x * 1.0f, velocity.y * 1.0f);

    for (auto& gameobject : GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetSceneObjectList()) {
        CheckCollisionsRecursively(gameobject);
    }

    // Move object
    Move(Vector2::Vector2<int>(movementDirection.x, movementDirection.y));

    if (!isKinematic && !isTrigger && !isSliding) {
        // Reset object velocity
        velocity = Vector2::Vector2(0, 0);
    }
}

void PhysicsComponent::SetVelocity(Vector2::Vector2<int> newVelocity) {
    velocity = newVelocity;
}

void PhysicsComponent::SetTeleportBehavior(bool newValue) {
    teleportOnBoundaries = newValue;
}

void PhysicsComponent::SetKinematic(bool newValue) {
    isKinematic = newValue;
}

void PhysicsComponent::SetSliding(bool newValue) {
    isSliding = newValue;
}

void PhysicsComponent::SetMovable(bool newValue) {
    isMovable = newValue;
}

void PhysicsComponent::Move(const Vector2::Vector2<int>& movementVector) {
    Vector2::Vector2<int> currentPosition = *objectLinkedTo->GetGlobalPosition();
    currentPosition += movementVector;

    Vector2::Vector2<int> objectDimensions = *objectLinkedTo->GetScale();

    if (teleportOnBoundaries) {
        if (currentPosition.x < 0) currentPosition.x = Graphics::SCREEN_WIDTH - objectDimensions.x;
        if (currentPosition.x + objectDimensions.x > Graphics::SCREEN_WIDTH) currentPosition.x = 0;
        if (currentPosition.y < 0) currentPosition.x = Graphics::SCREEN_HEIGHT - objectDimensions.y;
        if (currentPosition.y + objectDimensions.y > Graphics::SCREEN_HEIGHT) currentPosition.y = 0;
    }
    else {
        // Check window boundaries
        if (currentPosition.x < 0) currentPosition.x = 0;
        if (currentPosition.x + objectDimensions.x > Graphics::SCREEN_WIDTH) currentPosition.x = Graphics::SCREEN_WIDTH - objectDimensions.x;
        if (currentPosition.y < 0) currentPosition.y = 0;
        if (currentPosition.y + objectDimensions.y > Graphics::SCREEN_HEIGHT) currentPosition.y = Graphics::SCREEN_HEIGHT - objectDimensions.y;
    }

    objectLinkedTo->SetGlobalPosition(currentPosition);
}

void PhysicsComponent::CheckCollisionsRecursively(GameObject::GameObject* collisionCheckWith) {
    if (!collisionCheckWith->IsActive()) return;
    if (collisionCheckWith == objectLinkedTo) return;
    if (isKinematic) return;

    // Temporal fix, TODO: Collision mask
    if (collisionCheckWith->GetName().find("MapRow") != std::string::npos && objectLinkedTo->GetName().find("MapRow") != std::string::npos) return;

    PhysicsComponent* physics = static_cast<PhysicsComponent*>(collisionCheckWith->GetComponent("Physics"));

    // Perform collision detection
    if (physics != nullptr) {
        if (!physics->IsActive() || physics->isKinematic) return;
        if (physics->isTrigger && isTrigger) return;

        // Get objects info
        Vector2::Vector2<int> firstPosition = *objectLinkedTo->GetGlobalPosition();
        Vector2::Vector2<int> firstScale = *objectLinkedTo->GetScale();
        Vector2::Vector2<int> secondPosition = *collisionCheckWith->GetGlobalPosition();
        Vector2::Vector2<int> secondScale = *collisionCheckWith->GetScale();

        // Thanks to nightblade for this article
        // https://www.deengames.com/blog/2020/a-primer-on-aabb-collision-resolution.html
        // General AABB (broad phase)
        if (IsAabbCollision(
            firstPosition.x + velocity.x, firstPosition.y + velocity.y, firstScale.x, firstScale.y,
            secondPosition.x, secondPosition.y, secondScale.x, secondScale.y)) {

            PhysicsLogger::Instance().LogMessage("Collision detected: " + objectLinkedTo->GetName() + " + " + collisionCheckWith->GetName());

            // Sweep AABB (narrow phase)
            float dx, dy;

            dx = (firstPosition.x < secondPosition.x) ?
                secondPosition.x - (firstPosition.x + firstScale.x) : 
                firstPosition.x - (secondPosition.x + secondScale.x);

            dy = (firstPosition.y < secondPosition.y) ?
                secondPosition.y - (firstPosition.y + firstScale.y) :
                firstPosition.y - (secondPosition.y + secondScale.y);

            float xAxisTimeToCollide = velocity.x != 0 ? abs(dx / velocity.x) : 0;
            float yAxisTimeToCollide = velocity.y != 0 ? abs(dy / velocity.y) : 0;

            // Collision response
            float shortestTime = 0;

            if (!physics->isTrigger) {

                // Both objects move around the level and collide with each other
                if (isMovable && physics->isMovable) {
                    movementDirection = Vector2::Vector2<float>(0, 0);
                    physics->SetVelocity(Vector2::Vector2(0, 0));
                }

                // One of the objects move around the level
                else {
                    // Collision on X-axis only
                    if (velocity.x != 0 && velocity.y == 0) {
                        shortestTime = xAxisTimeToCollide;
                        movementDirection.x = shortestTime * velocity.x;

                        if (physics->isMovable && !isTrigger) physics->SetVelocity(Vector2::Vector2(velocity.x, 0));
                    }

                    // Collision on Y-axis only
                    else if (velocity.x == 0 && velocity.y != 0) {
                        shortestTime = yAxisTimeToCollide;
                        movementDirection.y = shortestTime * velocity.y;

                        if (physics->isMovable && !isTrigger) physics->SetVelocity(Vector2::Vector2(0, velocity.y));
                    }

                    // Collision on X and Y axis (eg. slide up against a wall)
                    else {
                        shortestTime = std::min(abs(xAxisTimeToCollide), abs(yAxisTimeToCollide));

                        movementDirection.x = shortestTime * velocity.x;
                        movementDirection.y = shortestTime * velocity.y;

                        if (physics->isMovable && !isTrigger) physics->SetVelocity(velocity);
                    }
                }
            }
            else {
                AbstractComponent* component;
                
                // Try to pick the object
                component = collisionCheckWith->GetComponent("Pickable");
                PickableComponent* pickable = static_cast<PickableComponent*>(component);
                if (pickable != nullptr) pickable->PickUp(objectLinkedTo);

                // Try to damage the object
                component = collisionCheckWith->GetComponent("Damageable");
                DamageableComponent* damageComponent = static_cast<DamageableComponent*>(component);
                
                AbstractComponent* secondComponent = objectLinkedTo->GetComponent("PlayerHealth");
                if (secondComponent == nullptr) secondComponent = objectLinkedTo->GetComponent("DestructibleHealth");

                HealthComponent* health = static_cast<HealthComponent*>(secondComponent);

                if (damageComponent != nullptr && health != nullptr && damageComponent->IsActive()) {
                    health->AdjustHealth(-1);
                    damageComponent->SetActive(false);
                }
            }
        }

        return;
    }

    for (auto& childObject : collisionCheckWith->GetChildObjects()) {
        CheckCollisionsRecursively(childObject);
    }
}

bool PhysicsComponent::IsAabbCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    return x1 < x2 + w2 &&
        x1 + w1 > x2 &&
        y1 < y2 + h2 &&
        y1 + h1 > y2;
}