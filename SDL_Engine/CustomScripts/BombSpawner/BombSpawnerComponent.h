#pragma once

#ifndef BombSpawnerComponent_H
#define BombSpawnerComponent_H

#include "../../Engine/Component/AbstractComponent.h"
#include "../../Engine/Timer/Timer.h"
#include "../BombComponent/BombComponent.h"

class ObjectPoolComponent;

class BombSpawnerComponent : public AbstractComponent {
public:
    void Init() override;
    void LoadConfig(const nlohmann::json& config) override;
    void Update() override;

    void PlaceBomb();

private:
    void DecreaseActiveBombs();

    ObjectPoolComponent* bombPool;

    Timer delayTimer;
    double previosFrameTime;

    std::string controllerAgentName;
    float placeDelay;
    double lastPlacedBombTime;
    int maxBombAmount;
    int bombPlaced = 0;
};

#endif