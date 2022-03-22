#include "SceneManager.h"

SceneManager::SceneManager() {
}

SceneManager::~SceneManager() {
    currentScene = nullptr;

    for (int sceneIndex = 0; sceneIndex < scenesToBuild.size(); sceneIndex++) {
        delete scenesToBuild[sceneIndex];
    }

    scenesToBuild.clear();
}

void SceneManager::AddScene(Scene* newScene) {
    scenesToBuild.push_back(newScene);
}

int SceneManager::GetCurrentSceneIndex() {
    return currentScene->GetID();
}

Scene* SceneManager::GetCurrentScene() {
    return currentScene;
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
        subscribers[index]->UpdateSceneEvent();
    }
}