#include "HealthComponent.h"
#include "../../Engine/GameManager.h"

HealthComponent::~HealthComponent() {
    delete model;
    delete view;
}

void HealthComponent::Init() {
    AbstractComponent::Init();
    if (viewNeeded) view->Init();
}

void HealthComponent::LoadConfig(const nlohmann::json& config) {
    viewNeeded = config.value("viewNeeded", false);

    model = new HealthComponentModel();
    model->AddHealth(config.value("initialHealth", 0));

    if (viewNeeded) {
        view = new HealthComponentView(model);
        view->LoadConfig(config.at("view"));
        view->UpdateHealthText();
    }
}

void HealthComponent::Render() {
    if (viewNeeded) view->Render();
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
    if (viewNeeded) view->UpdateHealthText();
}