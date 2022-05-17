#include "BombSpawnerComponent.h"
#include "../../Engine/GameManager.h"
#include "../../Engine/Component/ObjectPoolComponent/ObjectPoolComponent.h"

void BombSpawnerComponent::Init() {
    lastPlacedBombTime = placeDelay;

    // Get current scene
    Scene* currentScene = GameManager::Instance()->GetSceneManager()->GetCurrentScene();

    // Get delay timer
    delayTimer = currentScene->GetGameLoop()->GetTimer();

    // Get object pool
    GameObject::GameObject* poolHolderObject = currentScene->GetSceneObjectByName("BombPool");

    if (poolHolderObject == nullptr) Logger::Instance().LogError("Bomb Pool object was not found");

    bombPool = static_cast<ObjectPoolComponent*>(poolHolderObject->GetComponent("ObjectPool"));

    // Get input controller and link action of placing bomb
    InputController* inputController = currentScene->GetInputConfigurator()->GetInputController();
    
    if (controllerAgentName == "Player1") inputController->LinkAction("player1PlantBomb", std::bind(&BombSpawnerComponent::PlaceBomb, this));
    if (controllerAgentName == "Player2") inputController->LinkAction("player2PlantBomb", std::bind(&BombSpawnerComponent::PlaceBomb, this));
}

void BombSpawnerComponent::LoadConfig(const nlohmann::json& config) {
    controllerAgentName = config.at("playerName");
    placeDelay = config.value("placeDelay", 1.0f);
    maxBombAmount = config.value("maxBombs", 1);
}

void BombSpawnerComponent::Update() {
    double currentTime = delayTimer.GetCurrentTime();

    lastPlacedBombTime += currentTime - previosFrameTime;
    previosFrameTime = currentTime;
}

void BombSpawnerComponent::PlaceBomb() {
    if (lastPlacedBombTime < placeDelay || bombPlaced >= maxBombAmount) return;

    GameObject::GameObject* bombObject = bombPool->GetPoolObject();
    if (bombObject == nullptr) {
        Logger::Instance().LogError("Getting bomb from pool has been failed!");
        return;
    }

    lastPlacedBombTime = 0;
    bombPlaced++;

    bombObject->SetGlobalPosition(*objectLinkedTo->GetGlobalPosition());
    Logger::Instance().LogMessage(controllerAgentName + " placed a bomb!");

    AnimationComponent* animationComponent = static_cast<AnimationComponent*>(bombObject->GetComponent("Animation"));
    animationComponent->PlayAnimation("bombTicking");

    BombComponent* bombComponent = static_cast<BombComponent*>(bombObject->GetComponent("Bomb"));

    // Last frame events
    animationComponent->AddFrameEvent(
        std::bind(&BombComponent::Explode, bombComponent)
    );

    // Decrease amount of currently placed bombs for player
    animationComponent->AddFrameEvent(
        std::bind(&BombSpawnerComponent::DecreaseActiveBombs, this)
    );

    animationComponent->AddFrameEvent(
        std::bind(&GameObject::GameObject::Deactivate, bombObject)
    );
}

void BombSpawnerComponent::DecreaseActiveBombs() {
    bombPlaced--;
}
