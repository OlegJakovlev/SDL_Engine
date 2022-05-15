#pragma once

#ifndef ComponentFactory_H
#define ComponentFactory_H

#include <string>
#include "../../Component/AbstractComponent.h"

// Base
#include "../../Component/TextComponent/TextComponent.h"
#include "../../Component/ImageComponent/ImageComponent.h"
#include "../../Component/AnimationComponent/AnimationComponent.h"
#include "../../Component/PhysicsComponent/PhysicsComponent.h"
#include "../../Component/ObjectPoolComponent/ObjectPoolComponent.h"

// Composite
#include "../../../CustomScripts/GameLoopView.h"
#include "../../../CustomScripts/PlayerMovement/PlayerMovement.h"
#include "../../../CustomScripts/ScoreComponent/ScoreComponent.h"
#include "../../../CustomScripts/HealthComponent/HealthComponent.h"
#include "../../../CustomScripts/BombSpawner/BombSpawnerComponent.h"
#include "../../../CustomScripts/TimerComponent/TimerComponent.h"
#include "../../../CustomScripts/PickableComponent/PickableComponent.h"
#include "../../../CustomScripts/TimerPowerUp/TimerPowerUp.h"
#include "../../../CustomScripts/CoinPickUp/CoinPickUp.h"
#include "../../../CustomScripts/MenuView/MenuView.h"

class ComponentFactory {
public:
    ~ComponentFactory();

    static ComponentFactory* Instance();
    AbstractComponent* CreateComponent(const std::string& componentName);

private:
    ComponentFactory() = default;
    static ComponentFactory* sInstance;
};

#endif