#include "HealthComponent.h"

HealthComponent::~HealthComponent() {
    delete model;
    delete view;
}

void HealthComponent::Init() {
    AbstractComponent::Init();
    view->Init();
}

void HealthComponent::LoadConfig(const nlohmann::json& config) {
    model = new HealthComponentModel();
    view = new HealthComponentView(*model);

    view->LoadConfig(config.at("view"));
}

void HealthComponent::Render() {
    view->Render();
}

void HealthComponent::AdjustHealth(int healthAdjustment) {
    // Update model
    if (healthAdjustment < 0) {
        model->SubstractHealth(healthAdjustment * -1);
    }
    else {
        model->AddHealth(healthAdjustment);
    }

    // Update view
    view->UpdateHealthText();
}