#pragma once

#ifndef PickableComponent_H
#define PickableComponent_H

#include "../../Engine/Component/AbstractComponent.h"
#include "../../Engine/Component/PhysicsComponent/PhysicsComponent.h"
#include "../../Engine/Component/AnimationComponent/AnimationComponent.h"
#include "../../Engine/Locator/AudioLocator/AudioLocator.h"

class PickableComponent : public AbstractComponent {
public:
    void Init() override;
    void LoadConfig(const nlohmann::json& config) override;

    void AddPickUpEvent(std::function<void()> newEvent);

    virtual void PickUp();
    virtual void PickUp(GameObject::GameObject* newPickerObject);

    GameObject::GameObject* GetPickerObject();

private:
    AnimationComponent* animationComponent;

    GameObject::GameObject* pickerObject;
    std::vector<std::function<void()>> pickUpEvents;
    
    std::string idleAnimationName;
    std::string pickUpSoundName;
    std::string pickUpAnimationName;

};

#endif