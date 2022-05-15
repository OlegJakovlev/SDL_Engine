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

    // Sort scenes by ID
    std::sort(scenesToBuild.begin(), scenesToBuild.end(), [](const Scene* first, const Scene* second) -> bool {
        return first->GetID() < second->GetID();
    });
}

int SceneManager::GetCurrentSceneIndex() {
    return currentScene->GetID();
}

Scene* SceneManager::GetCurrentScene() {
    return currentScene;
}

void SceneManager::SetCurrentSceneByID(int targetSceneID) {
    if (targetSceneID < 0 || targetSceneID >= scenesToBuild.size()) return;

    currentScene->Reset();

    // Set new scene
    currentScene = scenesToBuild.at(targetSceneID);
}

void SceneManager::SetCurrentSceneByName(std::string targetSceneName) {
    for (auto& scene : scenesToBuild) {
        if (scene->GetName() == targetSceneName) {
            currentScene->Reset();

            // Set new scene
            currentScene = scene;
            return;
        }
    }
}

void SceneManager::LoadNextScene() {
    Logger::Instance().LogMessage("Loading next scene...");
    SetCurrentSceneByID(currentScene->GetID() + 1);
}

void SceneManager::LoadPreviousScene() {
    Logger::Instance().LogMessage("Loading previous scene...");
    SetCurrentSceneByID(currentScene->GetID() - 1);
}
