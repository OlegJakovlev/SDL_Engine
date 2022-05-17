#include "BombComponent.h"
#include "../../Engine/GameManager.h"
#include "../../Engine/Component/ObjectPoolComponent/ObjectPoolComponent.h"

void BombComponent::Init() {
    // Get current scene
    Scene* currentScene = GameManager::Instance()->GetSceneManager()->GetCurrentScene();

    // Get object pool
    GameObject::GameObject* poolHolderObject = currentScene->GetSceneObjectByName("ExplosionPool");

    if (poolHolderObject == nullptr) Logger::Instance().LogError("Explosion Pool object was not found");

    explosionPool = static_cast<ObjectPoolComponent*>(poolHolderObject->GetComponent("ObjectPool"));
}

void BombComponent::Explode() {
    GameObject::GameObject* explosionObject = explosionPool->GetPoolObject();
    if (explosionObject == nullptr) {
        Logger::Instance().LogError("Getting bomb from pool has been failed!");
        return;
    }

    explosionObject->SetLocalPosition(*objectLinkedTo->GetGlobalPosition());

    ExplosionComponent* explosionComponent = static_cast<ExplosionComponent*>(explosionObject->GetComponent("Explosion"));
    explosionComponent->Explode();
}