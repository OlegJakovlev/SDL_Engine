#include "ComponentFactory.h"

ComponentFactory* ComponentFactory::sInstance = nullptr;

ComponentFactory* ComponentFactory::Instance() {
    if (sInstance == nullptr) sInstance = new ComponentFactory();
    return sInstance;
}

IComponent* ComponentFactory::CreateComponent(const std::string& componentName) {
    if (componentName == "Text") {
        return new TextComponent();
    }
    else if (componentName == "") {

    }

    return nullptr;
}
