#include "BombSpawnerComponent.h"
#include "../../Engine/GameManager.h"
#include "../../Engine/Component/ObjectPoolComponent/ObjectPoolComponent.h"

void BombSpawnerComponent::Init() {
    GameObject::GameObject* poolHolderObject = GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetSceneObjectByName("BombPool");

    if (poolHolderObject == nullptr) {
        Logger::Instance().LogError("Bomb Pool object was not found");
    }
    
    bombPool = static_cast<ObjectPoolComponent*>(poolHolderObject->GetComponent("ObjectPool"));

    // Get input controller and link action of placing bomb
    InputController* inputController = GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetInputConfigurator()->GetInputController();
    
    if (controllerAgentName == "Player1") {
        inputController->LinkAction("player1PlantBomb", std::bind(&BombSpawnerComponent::PlaceBomb, this));
    }

    if (controllerAgentName == "Player2") {
        inputController->LinkAction("player2PlantBomb", std::bind(&BombSpawnerComponent::PlaceBomb, this));
    }
}

void BombSpawnerComponent::LoadConfig(const nlohmann::json& config) {
    controllerAgentName = config.at("playerName");
}

void BombSpawnerComponent::PlaceBomb() {
    GameObject::GameObject* bombObject = bombPool->GetPoolObject();
    if (bombObject == nullptr) {
        Logger::Instance().LogError("Getting bomb from pool has been failed!");
        return;
    }

    bombObject->SetGlobalPosition(*objectLinkedTo->GetGlobalPosition());
    Logger::Instance().LogMessage(controllerAgentName + " placed a bomb!");

    AnimationComponent* animationComponent = static_cast<AnimationComponent*>(bombObject->GetComponent("Animation"));
    animationComponent->PlayAnimation("bombExplosion");
}
