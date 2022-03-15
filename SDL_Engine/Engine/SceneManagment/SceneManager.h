#pragma once

#ifndef SceneManager_H
#define SceneManager_H

#include <vector>
#include "Scene.h"

class SceneManager {
    Scene* currentScene;
    std::vector<Scene*> scenesToBuild;
};

#endif
