#include "PickableComponent.h"
#include "../../Engine/GameObject/GameObject.h"

void PickableComponent::Init() {
    animationComponent = static_cast<AnimationComponent*>(objectLinkedTo->GetComponent("Animation"));

    if (animationComponent != nullptr) animationComponent->PlayAnimation(idleAnimationName);
}

void PickableComponent::LoadConfig(const nlohmann::json& config) {
    pickUpSoundName = config.value("soundName", "");
    pickUpAnimationName = config.value("pickUpAnimation", "");
    idleAnimationName = config.value("idleAnimation", "");
}

void PickableComponent::AddPickUpEvent(std::function<void()> newEvent) {
    pickUpEvents.push_back(newEvent);
}

void PickableComponent::PickUp() {
    if (animationComponent != nullptr) {
        animationComponent->PlayAnimation(pickUpAnimationName);
        animationComponent->AddFrameEvent(std::bind(&GameObject::GameObject::Destroy, objectLinkedTo));
    }

    AudioLocator::GetAudio()->PlaySound(pickUpSoundName);

    // Execute all the additional events
    for (auto& pickUpEvent : pickUpEvents) {
        pickUpEvent();
    }

    if (animationComponent == nullptr || pickUpAnimationName == "") objectLinkedTo->Destroy();
}

void PickableComponent::PickUp(GameObject::GameObject* newPickerObject) {
    pickerObject = newPickerObject;
    PickUp();
}

GameObject::GameObject* PickableComponent::GetPickerObject() {
    return pickerObject;
}
