#include "FlyingBird.h"
#include "../../Engine/GameObject/GameObject.h"

void FlyingBird::Init() {
    physics = static_cast<PhysicsComponent*>(objectLinkedTo->GetComponent("Physics"));
    animator = static_cast<AnimationComponent*>(objectLinkedTo->GetComponent("Animation"));

    physics->SetKinematic(true);
    physics->SetTeleportBehavior(true);

    // Set random direction
    srand(time(0));
    int xVelocity = rand() % MAX_SPEED_X - MAX_SPEED_X / 2;
    int yVelocity = rand() % MAX_SPEED_Y - MAX_SPEED_Y / 2;

    if (xVelocity == 0 && yVelocity == 0) xVelocity = 2;

    physics->SetVelocity(Vector2::Vector2<int>(xVelocity, yVelocity));
    animator->PlayAnimation((xVelocity < 0) ? "flyingBirdLeft" : "flyingBirdRight");
}