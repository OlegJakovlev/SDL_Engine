#include "PlayerHealthComponent.h"
#include "../../../Engine/GameData/GameData.h"
#include "../../../Engine/GameManager.h"

void PlayerHealthComponent::Init() {
    HealthComponent::Init();

    animator = static_cast<AnimationComponent*>(objectLinkedTo->GetComponent("Animation"));

    timer = GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetGameLoop()->GetTimer();
    lastTimeDamaged = timer.GetCurrentTime() - invincibilityTime;
}

void PlayerHealthComponent::LoadConfig(const nlohmann::json& config) {
    HealthComponent::LoadConfig(config);

    invincibilityTime = config.value("invincibilityTime", 1.00);
}

void PlayerHealthComponent::AdjustHealth(int healthAdjustment) {
    if (timer.GetCurrentTime() < lastTimeDamaged + invincibilityTime) return;
    lastTimeDamaged = timer.GetCurrentTime();

    HealthComponent::AdjustHealth(healthAdjustment);
    animator->PlayAnimation((objectLinkedTo->GetName() == "Player1" ? "player1Damaged" : "player2Damaged"));
    AudioLocator::GetAudio()->PlaySound("playerHurt");

    // If player is dead, reset score and end the game
    if (model->GetHealth() <= 0) {
        GameData::Instance()->ReplaceDataEntry(objectLinkedTo->GetName(), std::to_string(-1000));
        GameManager::Instance()->GetSceneManager()->LoadNextScene();
    }
}
