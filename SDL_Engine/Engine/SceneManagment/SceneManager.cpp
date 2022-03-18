#include "SceneManager.h"

SceneManager::SceneManager() {
#if _DEBUG
    currentScene = new Scene();
    scenesToBuild.push_back(currentScene);
#endif
}

SceneManager::~SceneManager() {
    currentScene = nullptr;
    scenesToBuild.clear();
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