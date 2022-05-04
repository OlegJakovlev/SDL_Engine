#include "SceneManager.h"

SceneManager::SceneManager() {
}

SceneManager::~SceneManager() {
    currentScene = nullptr;

    for (Scene* scene : scenesToBuild) {
        delete scene;
    }

    scenesToBuild.clear();
}

void SceneManager::AddScene(Scene* newScene) {
    if (currentScene == nullptr) currentScene = newScene;
    scenesToBuild.push_back(newScene);
}

int SceneManager::GetCurrentSceneIndex() {
    return currentScene->GetID();
}

Scene* SceneManager::GetCurrentScene() {
    return currentScene;
}

void SceneManager::SetCurrentSceneByID(int targetSceneID) {
    if (targetSceneID < 0 || targetSceneID > scenesToBuild.size()) return;

    // Deallocate resources
    delete currentScene;

    // Set new scene
    currentScene = scenesToBuild.at(targetSceneID);
}

void SceneManager::SetCurrentSceneByName(std::string targetSceneName) {
    for (auto& scene : scenesToBuild) {
        if (scene->GetName() == targetSceneName) {
            // Deallocate resources
            delete currentScene;

            // Set new scene
            currentScene = scene;
            return;
        }
    }
}

void SceneManager::Subscribe(IObserver* newSubscriber) {
    subscribers.push_back(newSubscriber);
}

void SceneManager::Unsubscribe(IObserver* subscriber) {
    auto it = std::find(subscribers.begin(), subscribers.end(), subscriber);
    if (it != subscribers.end()) subscribers.erase(it);
}

void SceneManager::Notify() {
    for (int index = 0; index < subscribers.size(); index++) {
        subscribers[index]->UpdateEvent();
    }
}