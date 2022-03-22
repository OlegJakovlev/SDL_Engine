#include "SceneConfigurator.h"

SceneConfigurator::SceneConfigurator(const std::string& newConfigPath) : Configurator(newConfigPath) {
}

SceneConfigurator::~SceneConfigurator() {
    delete sceneManager;
}

void SceneConfigurator::LoadConfiguration() {
    Configurator::LoadConfiguration();

    sceneManager = new SceneManager();

    for (auto sceneToConfigure : configuration.at("root")) {
        // Create scene and add to scene manager
        Scene* newCreatedScene = new Scene(sceneToConfigure.at("ID").get<int>(), sceneToConfigure.at("name").get<std::string>());
        sceneManager->AddScene(newCreatedScene);

        // Create root element and all it child
        GameObject::GameObject* rootElement = new GameObject::GameObject(sceneToConfigure.at("gameObjects"));

        // Add all objects to scene
        newCreatedScene->AddSceneObject(rootElement);
    }
}
