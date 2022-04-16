#include "GameObjectFactory.h"

GameObjectFactory* GameObjectFactory::sInstance = nullptr;
int GameObjectFactory::nextID = 0;

GameObjectFactory* GameObjectFactory::Instance() {
    if (sInstance == nullptr) sInstance = new GameObjectFactory();
    return sInstance;
}

GameObject::GameObject* GameObjectFactory::CreateGameObject() {
    return new GameObject::GameObject(nextID++, "");
}

GameObject::GameObject* GameObjectFactory::CreateGameObject(const std::string& name) {
    return new GameObject::GameObject(nextID++, name);
}

GameObject::GameObject* GameObjectFactory::CreateGameObject(nlohmann::json config) {
    GameObject::GameObject* newGameObject = new GameObject::GameObject(config);

    for (nlohmann::json& childConfig : config.at("childObjects")) {
        // Construct child objects
        GameObject::GameObject* childObject = CreateGameObject(childConfig);

        // Link parent and child
        newGameObject->AddChildObject(childObject);
        childObject->SetParentObject(newGameObject);
    }

    return newGameObject;
}

GameObject::GameObject* GameObjectFactory::CreateGameObjectFromFile(const std::string& filename) {
    nlohmann::json statsViewConfiguration;
    std::ifstream file(filename);
    file >> statsViewConfiguration;

    return CreateGameObject(statsViewConfiguration.at("gameObjects"));
}
