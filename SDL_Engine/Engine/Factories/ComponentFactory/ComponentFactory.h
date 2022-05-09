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

class ComponentFactory {
public:
    static ComponentFactory* Instance();
    AbstractComponent* CreateComponent(const std::string& componentName);

private:
    ComponentFactory() = default;
    static ComponentFactory* sInstance;
};

#endif