#include "AbstractComponent.h"
#include "../GameObject/GameObject.h"

void AbstractComponent::Init() {
    SyncWithObject();
}

void AbstractComponent::LoadConfig(const nlohmann::json& config) {
}

void AbstractComponent::Update() {
}

void AbstractComponent::Render() {
}

void AbstractComponent::LinkWithObject(GameObject::GameObject* componentHolder) {
    objectLinkedTo = componentHolder;
}

void AbstractComponent::SyncWithObject() {
    const Vector2::Vector2<int>* renderPosition = objectLinkedTo->GetGlobalPosition();
    renderHolder.x = renderPosition->GetX();
    renderHolder.y = renderPosition->GetY();

    const Vector2::Vector2<int>* renderScale = objectLinkedTo->GetScale();
    renderHolder.w = renderScale->GetX();
    renderHolder.h = renderScale->GetY();
}
