#pragma once

#ifndef DestructibleHealthComponent_H
#define DestructibleHealthComponent_H

#include "../HealthComponent.h"
#include "../../../Engine/Component/ImageComponent/ImageComponent.h"

class DestructibleHealthComponent : public HealthComponent {
public:
    void Init() override;
    void AdjustHealth(int healthAdjustment) override;

private:
    ImageComponent* image;
    SDL_Texture* grassTexture;
};

#endif