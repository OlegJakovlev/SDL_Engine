#include "PhysicsComponent.h"
#include "../../GameManager.h"

PhysicsComponent::~PhysicsComponent() {
}

void PhysicsComponent::LoadConfig(const nlohmann::json& config) {
    isTrigger = config.value("IsTrigger", false);
}

void PhysicsComponent::Update() {
    movementDirection = Vector2::Vector2(velocity.x * 1.0f, velocity.y * 1.0f);

    for (auto& gameobject : GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetSceneObjectList()) {
        CheckCollisionsRecursively(gameobject);
    }

    // Move object
    Move(Vector2::Vector2<int>(movementDirection.x, movementDirection.y));

    // Reset object velocity
    velocity = Vector2::Vector2(0, 0);
}

void PhysicsComponent::SetVelocity(Vector2::Vector2<int> newVelocity) {
    velocity = newVelocity * 32;
}

void PhysicsComponent::Move(const Vector2::Vector2<int>& movementVector) {
    Vector2::Vector2<int> currentPosition = *objectLinkedTo->GetGlobalPosition();
    currentPosition += movementVector;

    Vector2::Vector2<int> objectDimensions = *objectLinkedTo->GetScale();

    // Check window boundaries
    if (currentPosition.x < 0) currentPosition.x = 0;
    if (currentPosition.x + objectDimensions.x > Graphics::SCREEN_WIDTH) currentPosition.x = Graphics::SCREEN_WIDTH - objectDimensions.x;
    if (currentPosition.y < 0) currentPosition.y = 0;
    if (currentPosition.y + objectDimensions.y > Graphics::SCREEN_HEIGHT) currentPosition.y = Graphics::SCREEN_HEIGHT - objectDimensions.y;

    objectLinkedTo->SetGlobalPosition(currentPosition);
}

void PhysicsComponent::CheckCollisionsRecursively(GameObject::GameObject* collisionCheckWith) {
    if (!collisionCheckWith->IsActive()) return;
    if (collisionCheckWith == objectLinkedTo) return;

    PhysicsComponent* physics = static_cast<PhysicsComponent*>(collisionCheckWith->GetComponent("Physics"));

    // Perform collision detection
    if (physics != nullptr) {

        // Get objects info
        Vector2::Vector2<int> firstPosition = *objectLinkedTo->GetGlobalPosition();
        Vector2::Vector2<int> firstScale = *objectLinkedTo->GetScale();
        Vector2::Vector2<int> secondPosition = *collisionCheckWith->GetGlobalPosition();
        Vector2::Vector2<int> secondScale = *collisionCheckWith->GetScale();

        // Thanks to nightblade for this article
        // https://www.deengames.com/blog/2020/a-primer-on-aabb-collision-resolution.html
        if (IsAabbCollision(
            firstPosition.x + velocity.x, firstPosition.y + velocity.y, firstScale.x, firstScale.y,
            secondPosition.x, secondPosition.y, secondScale.x, secondScale.y)) {

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
                if (velocity.x != 0 && velocity.y == 0)
                {
                    // Collision on X-axis only
                    shortestTime = xAxisTimeToCollide;
                    movementDirection.x = shortestTime * velocity.x;
                }
                else if (velocity.x == 0 && velocity.y != 0)
                {
                    // Collision on Y-axis only
                    shortestTime = yAxisTimeToCollide;
                    movementDirection.y = shortestTime * velocity.y;
                }
                else {
                    // Collision on X and Y axis (eg. slide up against a wall)
                    shortestTime = std::min(abs(xAxisTimeToCollide), abs(yAxisTimeToCollide));

                    movementDirection.x = shortestTime * velocity.x;
                    movementDirection.y = shortestTime * velocity.y;
                }
            }
            else {
                PickableComponent* pickable = static_cast<PickableComponent*>(collisionCheckWith->GetComponent("Pickable"));
                if (pickable == nullptr) return;

                pickable->PickUp(objectLinkedTo);
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