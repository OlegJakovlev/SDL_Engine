#include "AbstractComponent.h"
#include "../GameObject/GameObject.h"

void AbstractComponent::Init() {
    SyncWithObject();
}

void AbstractComponent::Reset() {
}

void AbstractComponent::LoadConfig(const nlohmann::json& config) {
}

void AbstractComponent::Update() {
    SyncWithObject();
}

void AbstractComponent::Render() {
}

void AbstractComponent::LinkWithObject(GameObject::GameObject* componentHolder) {
    objectLinkedTo = componentHolder;
}

void AbstractComponent::SetActive(bool newValue) {
    isActive = newValue;
}

bool AbstractComponent::IsActive() const {
    return isActive;
}

void AbstractComponent::SyncWithObject() {
    const Vector2::Vector2<int>* renderPosition = objectLinkedTo->GetGlobalPosition();
    renderHolder.x = renderPosition->x;
    renderHolder.y = renderPosition->y;

    const Vector2::Vector2<int>* renderScale = objectLinkedTo->GetScale();
    renderHolder.w = renderScale->x;
    renderHolder.h = renderScale->y;
}
