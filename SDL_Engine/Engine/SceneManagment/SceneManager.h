#pragma once

#ifndef SceneManager_H
#define SceneManager_H

#include <vector>
#include "Scene.h"
#include "../Logger/SceneLogger/SceneLogger.h"

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    Scene* GetCurrentScene();

    void AddScene(Scene* newScene);
    int GetCurrentSceneIndex();
    void SetCurrentSceneByID(int targetSceneID);
    void SetCurrentSceneByName(std::string targetSceneName);

private:
    Scene* currentScene;
    std::vector<Scene*> scenesToBuild;
};

#endif
