#pragma once

#ifndef AbstractComponent_H
#define AbstractComponent_H

#include "IComponent.h"
#include <SDL_rect.h>

namespace GameObject {
    class GameObject;
}

class AbstractComponent : public IComponent {
public:
    void Init() override;
    void Reset() override;
    void LoadConfig(const nlohmann::json& config) override;
    void Update() override;
    void Render() override;

    void LinkWithObject(GameObject::GameObject* componentHolder);
    void SetActive(bool newValue);
    bool IsActive() const;

protected:
    void SyncWithObject();

    bool isActive = true;
    GameObject::GameObject* objectLinkedTo;
    SDL_Rect renderHolder;
};

#endif
