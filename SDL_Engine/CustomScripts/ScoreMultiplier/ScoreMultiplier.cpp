#include "ScoreMultiplier.h"
#include "../../Engine/GameObject/GameObject.h"

void ScoreMultiplier::Init() {
    pickableComponent = static_cast<PickableComponent*>(objectLinkedTo->GetComponent("Pickable"));
    if (pickableComponent == nullptr) return;
    
    pickableComponent->AddPickUpEvent(std::bind(&ScoreMultiplier::CustomPickUp, this));
}

void ScoreMultiplier::CustomPickUp() {
    GameObject::GameObject* picker = pickableComponent->GetPickerObject();
    if (picker == nullptr) return;

    ScoreComponent* pickerScoreComponent = static_cast<ScoreComponent*>(picker->GetComponent("PlayerScore"));
    pickerScoreComponent->TurnOnMultiplier(15);
}
