#include "TimerPowerUp.h"
#include "../../Engine/GameManager.h"

void TimerPowerUp::Init() {
    GameObject::GameObject* timerObject = GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetSceneObjectByName("LevelTimer");
    if (timerObject == nullptr) return;
    
    levelTimer = static_cast<TimerComponent*>(timerObject->GetComponent("LevelTimer"));

    pickableComponent = static_cast<PickableComponent*>(objectLinkedTo->GetComponent("Pickable"));
    if (pickableComponent == nullptr) return;
    
    pickableComponent->AddPickUpEvent(std::bind(&TimerPowerUp::CustomPickUp, this));
}

void TimerPowerUp::CustomPickUp() {
    levelTimer->AddGamePlayTime(15);

    GameObject::GameObject* picker = pickableComponent->GetPickerObject();
    if (picker == nullptr) return;

    ScoreComponent* pickerScoreComponent = static_cast<ScoreComponent*>(picker->GetComponent("PlayerScore"));
    pickerScoreComponent->AdjustScore(5);
}
