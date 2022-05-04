#include "ComponentFactory.h"

ComponentFactory* ComponentFactory::sInstance = nullptr;

ComponentFactory* ComponentFactory::Instance() {
    if (sInstance == nullptr) sInstance = new ComponentFactory();
    return sInstance;
}

AbstractComponent* ComponentFactory::CreateComponent(const std::string& componentName) {
    // Base components
    if (componentName == "Text") {
        return new TextComponent();
    }
    
    if (componentName == "Image") {
        return new ImageComponent();
    }

    // Composite components
    if (componentName == "GameLoopView") {
        return new GameLoopView();
    }

    return nullptr;
}
