#pragma once

#ifndef ComponentFactory_H
#define ComponentFactory_H

#include <string>
#include "../../Component/IComponent.h"
#include "../../Component/TextComponent/TextComponent.h"

class ComponentFactory {
public:
    static ComponentFactory* Instance();
    IComponent* CreateComponent(const std::string& componentName);

private:
    ComponentFactory() = default;
    static ComponentFactory* sInstance;
};

#endif