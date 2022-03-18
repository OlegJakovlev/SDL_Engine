#include "SceneManager.h"

SceneManager::SceneManager() {
    currentScene = new Scene();
    scenesToBuild.push_back(currentScene);
}

SceneManager::~SceneManager() {
    currentScene = nullptr;
    scenesToBuild.clear();
}

Scene* SceneManager::GetCurrentScene() {
    return currentScene;
}
