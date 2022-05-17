#include "HealthComponent.h"
#include "../../Engine/GameManager.h"

HealthComponent::~HealthComponent() {
    delete model;
    delete view;
}

void HealthComponent::Init() {
    AbstractComponent::Init();
    view->Init();

    timer = GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetGameLoop()->GetTimer();
    lastTimeDamaged = timer.GetCurrentTime() - invincibilityTime;
}

void HealthComponent::LoadConfig(const nlohmann::json& config) {
    model = new HealthComponentModel();
    view = new HealthComponentView(model);

    view->LoadConfig(config.at("view"));
    model->AddHealth(config.value("initialHealth", 0));
    invincibilityTime = config.value("invincibilityTime", 1.00);

    view->UpdateHealthText();
}

void HealthComponent::Render() {
    view->Render();
}

void HealthComponent::AdjustHealth(int healthAdjustment) {
    if (timer.GetCurrentTime() < lastTimeDamaged + invincibilityTime) return;
    lastTimeDamaged = timer.GetCurrentTime();

    // Update model
    if (healthAdjustment < 0) {
        model->SubstractHealth(healthAdjustment * -1);
    }
    else {
        model->AddHealth(healthAdjustment);
    }

    // Update view
    view->UpdateHealthText();

    // If player is dead, reset score and end the game
    if (model->GetHealth() <= 0) {
        GameData::Instance()->ReplaceDataEntry(objectLinkedTo->GetName(), std::to_string(-1000));
        GameManager::Instance()->GetSceneManager()->LoadNextScene();
    }
}