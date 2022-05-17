#include "ExplosionComponent.h"
#include "../../Engine/GameObject/GameObject.h"

void ExplosionComponent::Init() {
    for (auto& child : objectLinkedTo->GetChildObjects()) {
        child->Initialize();
    }
}

void ExplosionComponent::Update() {
    for (auto& child : objectLinkedTo->GetChildObjects()) {
        child->Update();
    }
}

void ExplosionComponent::Explode() {
    for (auto& child : objectLinkedTo->GetChildObjects()) {
        child->UpdateGlobalTransform();

        DamageableComponent* damage = static_cast<DamageableComponent*>(child->GetComponent("Damageable"));
        if (damage) damage->SetActive(true);

        AnimationComponent* animator = static_cast<AnimationComponent*>(child->GetComponent("Animation"));
        if (animator) {
            animator->PlayAnimation("bombExplosion");
            animator->AddFrameEvent(std::bind(&GameObject::GameObject::Deactivate, objectLinkedTo));
        }
    }
}