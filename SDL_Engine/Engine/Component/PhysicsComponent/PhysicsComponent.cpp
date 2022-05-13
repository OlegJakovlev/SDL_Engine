#include "PhysicsComponent.h"
#include "../../GameManager.h"
#include "stdio.h"

PhysicsComponent::~PhysicsComponent() {
}

void PhysicsComponent::LoadConfig(const nlohmann::json& config) {
    isTrigger = config.value("IsTrigger", false);
}

void PhysicsComponent::Update() {
    for (auto& gameobject : GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetSceneObjectList()) {
        CheckCollisionsRecursively(gameobject);
    }

    Vector2::Vector2<float> normalizedMovement = velocity.Normalize() * 16.0;

    // Move object
    Move(Vector2::Vector2<int>(normalizedMovement.x, normalizedMovement.y));

    // Reset object velocity
    velocity = Vector2::Vector2(0, 0);
}

void PhysicsComponent::AdjustVelocityXComponent(int deltaXSpeed) {
    velocity.x += deltaXSpeed;
    if (velocity.x > 1) velocity.x = 1;
    if (velocity.x < -1) velocity.x = -1;
}

void PhysicsComponent::AdjustVelocityYComponent(int deltaYSpeed) {
    velocity.y += deltaYSpeed;
    if (velocity.y > 1) velocity.y = 1;
    if (velocity.y < -1) velocity.y = -1;
}

void PhysicsComponent::AddCollisionResponseEvent(const std::function<void()>& function) {
    collisionResponseEvents.push_back(function);
}

void PhysicsComponent::Move(const Vector2::Vector2<int>& movementVector) {
    Vector2::Vector2<int> currentPosition = Vector2::Vector2<int>(*objectLinkedTo->GetGlobalPosition());
    objectLinkedTo->SetGlobalPosition(currentPosition + movementVector);
}

void PhysicsComponent::CheckCollisionsRecursively(GameObject::GameObject* collisionCheckWith) {
    if (collisionCheckWith == objectLinkedTo) return;

    // Perform collision detection
    if (collisionCheckWith->GetComponent("Physics") != nullptr) {
        // CD broad phase
        if (AABBOverlap(collisionCheckWith)) {
            PhysicsLogger::Instance().LogMessage("Collision detected in broad phase!");

            // CD narrow phase
            float collisionTime = SweptAABB(collisionCheckWith);
            if (collisionTime != 1.0f) PhysicsLogger::Instance().LogMessage("Collision detected in narrow phase!");
            else return;

            // Calculate and round position difference
            float remainingTime = 1.0f - collisionTime;
            float dotProduct = Vector2::Vector2<float>::DotProduct(Vector2::Vector2<float>(velocity.x, velocity.y), normal) * collisionTime;

            // Call events on collision
            for (auto& eventName : collisionResponseEvents) {
                eventName();
            }

            if (!isTrigger) {
                std::printf("%s: Normal X:%f \t NormalY:%f \t VelocityX:%i\t VelocityY:%i \t DotProduct:%f \n", objectLinkedTo->GetName().c_str(), normal.x, normal.y, velocity.x, velocity.y, dotProduct);

                velocity *= -1;

                //velocity.x *= collisionTime;
                //velocity.y *= collisionTime;

                //velocity.x = dotProduct * normal.x;
                //velocity.y = dotProduct * normal.y;

                std::printf("%s: Normal X:%f \t NormalY:%f \t VelocityX:%i\t VelocityY:%i \t DotProduct:%f \n", objectLinkedTo->GetName().c_str(), normal.x, normal.y, velocity.x, velocity.y, dotProduct);
            }

            return;
        }
    }

    for (auto& childObject : collisionCheckWith->GetChildObjects()) {
        CheckCollisionsRecursively(childObject);
    }
}

bool PhysicsComponent::AABBOverlap(GameObject::GameObject* checkOverlapWith) {
    // Get objects info
    const Vector2::Vector2<int>* firstPosition = objectLinkedTo->GetGlobalPosition();
    const Vector2::Vector2<int>* firstScale = objectLinkedTo->GetScale();
    const Vector2::Vector2<int>* secondPosition = checkOverlapWith->GetGlobalPosition();
    const Vector2::Vector2<int>* secondScale = checkOverlapWith->GetScale();

    // Calculate corners coordinates for first object
    int firstMinX = firstPosition->x;
    int firstMaxX = firstMinX + firstScale->x;
    int firstMinY = firstPosition->y;
    int firstMaxY = firstMinY + firstScale->y;

    // Calculate corners coordinates for second object
    int secondMinX = secondPosition->x;
    int secondMaxX = secondMinX + secondScale->x;
    int secondMinY = secondPosition->y;
    int secondMaxY = secondMinY + secondScale->y;

    // Calculate difference
    float d1x = secondMinX - firstMaxX;
    float d1y = secondMinY - firstMaxY;

    float d2x = firstMinX - secondMaxX;
    float d2y = firstMinY - secondMaxY;

    // Check if collision happened
    if ((d1x > 0.0f || d1y > 0.0f) || (d2x > 0.0f || d2y > 0.0f)) return false;

    return true;
}

// Returns the value between 0 and 1 desribing when the collision occurred
// https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084/
float PhysicsComponent::SweptAABB(GameObject::GameObject* secondBody) {
    // Get objects info
    const Vector2::Vector2<int>* firstPosition = objectLinkedTo->GetGlobalPosition();
    const Vector2::Vector2<int>* firstScale = objectLinkedTo->GetScale();
    const Vector2::Vector2<int>* secondPosition = secondBody->GetGlobalPosition();
    const Vector2::Vector2<int>* secondScale = secondBody->GetScale();

    int xInvEntry, yInvEntry; // Distance to the closest edge of the object
    int xInvExit, yInvExit; // Distance to the far sides of the object

    xInvEntry = (velocity.x > 0) ? 
        secondPosition->x - (firstPosition->x + firstScale->x) :
        (secondPosition->x + secondScale->x) - firstPosition->x;

    xInvExit = (velocity.x > 0) ?
        (secondPosition->x + secondScale->x) - firstPosition->x :
        secondPosition->x - (firstPosition->x + firstScale->x);

    yInvEntry = (velocity.y > 0) ?
        secondPosition->y - (firstPosition->y + firstScale->y) :
        (secondPosition->y + secondScale->y) - firstPosition->y;

    yInvExit = (velocity.y > 0) ?
        (secondPosition->y + secondScale->y) - firstPosition->y :
        secondPosition->y - (firstPosition->y + firstScale->y);

    // Find collision start and end times for each axis
    float xEntry, yEntry;
    float xExit, yExit;

    xEntry = (velocity.x == 0) ? -std::numeric_limits<int>::infinity() : xInvEntry / velocity.x;
    xExit = (velocity.x == 0) ? std::numeric_limits<int>::infinity() : xInvExit / velocity.x;

    yEntry = (velocity.y == 0) ? -std::numeric_limits<int>::infinity() : yInvEntry / velocity.y;
    yExit = (velocity.y == 0) ? std::numeric_limits<int>::infinity() : yInvExit / velocity.y;

    float entryTime = std::max(xEntry, yEntry);
    float exitTime = std::min(xExit, yExit);

    // No collision happened
    if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f) {
        normal = Vector2::Vector2<float>(0, 0);
        return 1.0f;
    }

    // Collision happened
    else {
        // Calculate normal of collided surface
        if (xEntry > yEntry) {
            normal.x = (xInvEntry) < 0 ? 1 : -1;
            normal.y = 0;
        }
        else {
            normal.x = 0;
            normal.y = (yInvEntry) < 0 ? 1 : -1;
        }
    }

    return entryTime;
}
