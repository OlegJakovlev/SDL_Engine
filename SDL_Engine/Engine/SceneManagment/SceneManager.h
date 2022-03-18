#pragma once

#ifndef SceneManager_H
#define SceneManager_H

#include <vector>
#include "Scene.h"

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    Scene* GetCurrentScene();

private:
    Scene* currentScene;
    std::vector<Scene*> scenesToBuild;
};

#endif
