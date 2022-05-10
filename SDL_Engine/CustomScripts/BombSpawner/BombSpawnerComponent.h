#pragma once

#ifndef BombSpawnerComponent_H
#define BombSpawnerComponent_H

#include "../../Engine/Component/AbstractComponent.h"

class ObjectPoolComponent;

class BombSpawnerComponent : public AbstractComponent {
public:
    void Init() override;
    void LoadConfig(const nlohmann::json& config) override;

    void PlaceBomb();

private:
    ObjectPoolComponent* bombPool;
    std::string controllerAgentName;
};

#endif