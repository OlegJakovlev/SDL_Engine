#include "CoinPickUp.h"
#include "../../Engine/GameObject/GameObject.h"

void CoinPickUp::Init() {
    pickableComponent = static_cast<PickableComponent*>(objectLinkedTo->GetComponent("Pickable"));
    if (pickableComponent == nullptr) return;
    
    pickableComponent->AddPickUpEvent(std::bind(&CoinPickUp::CustomPickUp, this));    
}

void CoinPickUp::CustomPickUp() {
    GameObject::GameObject* picker = pickableComponent->GetPickerObject();
    if (picker == nullptr) return;

    ScoreComponent* pickerScoreComponent = static_cast<ScoreComponent*>(picker->GetComponent("PlayerScore"));
    pickerScoreComponent->AdjustScore(1);
}
