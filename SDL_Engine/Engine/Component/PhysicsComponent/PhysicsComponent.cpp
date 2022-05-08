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
            Vector2::Vector2<float> deltaPosition = Vector2::Vector2<float>(velocity.GetX() * collisionTime, velocity.GetY() * collisionTime);
            float remainingtime = 1.0f - collisionTime;

            // Slide projection
            float dotProduct = Vector2::Vector2<float>::DotProduct(velocity, normal);
            velocity = Vector2::Vector2<float>(dotProduct * normal.GetY(), dotProduct * normal.GetX());
        }
    }

    // Move object
    Vector2::Vector2<int> currentPosition = Vector2::Vector2<int>(*objectLinkedTo->GetGlobalPosition());
    objectLinkedTo->SetGlobalPosition(currentPosition + Vector2::Vector2<int>(velocity.GetX(), velocity.GetY()));
}

bool PhysicsComponent::AABBOverlap(GameObject::GameObject* checkOverlapWith) {
    // Get objects info
    const Vector2::Vector2<int>* firstPosition = objectLinkedTo->GetGlobalPosition();
    const Vector2::Vector2<int>* firstScale = objectLinkedTo->GetScale();
    const Vector2::Vector2<int>* secondPosition = checkOverlapWith->GetGlobalPosition();
    const Vector2::Vector2<int>* secondScale = checkOverlapWith->GetScale();

    // Calculate corners coordinates for first object
    int firstMinX = firstPosition->GetX();
    int firstMaxX = firstMinX + firstScale->GetX();
    int firstMinY = firstPosition->GetY();
    int firstMaxY = firstMinY + firstScale->GetY();

    // Calculate corners coordinates for second object
    int secondMinX = secondPosition->GetX();
    int secondMaxX = secondMinX + secondScale->GetX();
    int secondMinY = secondPosition->GetY();
    int secondMaxY = secondMinY + secondScale->GetY();

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

    xInvEntry = (velocity.GetX() > 0) ? 
        secondPosition->GetX() - (firstPosition->GetX() + firstScale->GetX()) :
        (secondPosition->GetX() + secondScale->GetX()) - firstPosition->GetX();

    xInvExit = (velocity.GetX() > 0) ?
        (secondPosition->GetX() + secondScale->GetX()) - firstPosition->GetX() :
        secondPosition->GetX() - (firstPosition->GetX() + firstScale->GetX());

    yInvEntry = (velocity.GetY() > 0) ?
        secondPosition->GetY() - (firstPosition->GetY() + firstScale->GetY()) :
        (secondPosition->GetY() + secondScale->GetY()) - firstPosition->GetY();

    yInvExit = (velocity.GetY() > 0) ?
        (secondPosition->GetY() + secondScale->GetY()) - firstPosition->GetY() :
        secondPosition->GetY() - (firstPosition->GetY() + firstScale->GetY());

    // Find collision start and end times for each axis
    float xEntry, yEntry;
    float xExit, yExit;

    xEntry = (velocity.GetX() == 0) ? -std::numeric_limits<int>::infinity() : xInvEntry / velocity.GetX();
    xExit = (velocity.GetX() == 0) ? std::numeric_limits<int>::infinity() : xInvExit / velocity.GetX();

    yEntry = (velocity.GetY() == 0) ? -std::numeric_limits<int>::infinity() : yInvEntry / velocity.GetY();
    yExit = (velocity.GetY() == 0) ? std::numeric_limits<int>::infinity() : yInvExit / velocity.GetY();

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
            normal.SetX((xInvEntry) < 0 ? 1 : -1);
            normal.SetY(0);
        }
        else {
            normal.SetX(0);
            normal.SetY((yInvEntry) < 0 ? 1 : -1);
        }
    }

    return entryTime;
}
