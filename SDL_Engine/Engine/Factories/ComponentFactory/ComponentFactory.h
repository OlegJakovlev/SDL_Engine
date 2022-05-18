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
#include "../../../CustomScripts/HealthComponent/PlayerHealth/PlayerHealthComponent.h"
#include "../../../CustomScripts/HealthComponent/DestructibleObjectHealth/DestructibleHealthComponent.h"
#include "../../../CustomScripts/BombSpawner/BombSpawnerComponent.h"
#include "../../../CustomScripts/TimerComponent/TimerComponent.h"
#include "../../../CustomScripts/PickableComponent/PickableComponent.h"
#include "../../../CustomScripts/TimerPowerUp/TimerPowerUp.h"
#include "../../../CustomScripts/CoinPickUp/CoinPickUp.h"
#include "../../../CustomScripts/MenuView/MenuView.h"
#include "../../../CustomScripts/WinnerView/WinnerView.h"
#include "../../../CustomScripts/FlyingBird/FlyingBird.h"
#include "../../../CustomScripts/BombComponent/BombComponent.h"
#include "../../../CustomScripts/ExplosionComponent/ExplosionComponent.h"
#include "../../../CustomScripts/Damageable/DamageableComponent.h"
#include "../../../CustomScripts/ScoreMultiplier/ScoreMultiplier.h"

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