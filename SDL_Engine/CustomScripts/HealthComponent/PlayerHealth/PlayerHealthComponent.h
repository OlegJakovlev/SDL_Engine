#pragma once

#ifndef PlayerHealthComponent_H
#define PlayerHealthComponent_H

#include "../HealthComponent.h"
#include "../../../Engine/Component/AnimationComponent/AnimationComponent.h"

class PlayerHealthComponent : public HealthComponent {
public:
    void Init() override;
    void LoadConfig(const nlohmann::json& config) override;
    void AdjustHealth(int healthAdjustment) override;

private:
    Timer timer;
    double lastTimeDamaged;
    double invincibilityTime;

    AnimationComponent* animator;
};

#endif