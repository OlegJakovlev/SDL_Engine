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

void SceneManager::LoadNextScene() {
    SetCurrentSceneByID(currentScene->GetID() + 1);
}

void SceneManager::LoadPreviousScene() {
    SetCurrentSceneByID(currentScene->GetID() - 1);
}
