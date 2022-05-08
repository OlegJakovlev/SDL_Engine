#include "PhysicsComponent.h"
#include "../../GameManager.h"

PhysicsComponent::~PhysicsComponent() {
}

void PhysicsComponent::Update() {
    for (auto& gameobject : GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetSceneObjectList()) {
        if (gameobject->GetComponent("Physics") == nullptr) continue;

        // CD broad phase
        if (AABBOverlap(gameobject)) {
            PhysicsLogger::Instance().LogMessage("Collision detected in broad phase!");

            // CD narrow phase
            float collisionTime = SweptAABB(nullptr);
            if (collisionTime != 1.0f) PhysicsLogger::Instance().LogMessage("Collision detected in narrow phase!");

            // Calculate and round position difference
            Vector2::Vector2<float> deltaPosition = Vector2::Vector2<float>(velocity.x * collisionTime, velocity.y * collisionTime);
            float remainingtime = 1.0f - collisionTime;

            // Slide projection
            float dotProduct = Vector2::Vector2<float>::DotProduct(velocity, normal);
            velocity = Vector2::Vector2<float>(dotProduct * normal.y, dotProduct * normal.x);
        }
    }

    // Move object
    Vector2::Vector2<int> currentPosition = Vector2::Vector2<int>(*objectLinkedTo->GetGlobalPosition());
    objectLinkedTo->SetGlobalPosition(currentPosition + Vector2::Vector2<int>(velocity.x, velocity.y));
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

// https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084/
// Returns the value between 0 and 1 desribing when the collision occurred
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
