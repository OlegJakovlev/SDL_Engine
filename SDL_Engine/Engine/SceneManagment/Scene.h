#pragma once

#ifndef Scene_H
#define Scene_H

#include <vector>
#include "../GameObject/GameObject.h"
#include "../GameLoop/GameLoop.h"

class Scene {

public:
    Scene();
    ~Scene();

    GameLoop* GetGameLoop();
    InputController* GetInputController();
    std::vector<GameObject*>& GetSceneObjectList();

private:
    GameLoop* gameLoop;
    InputController* inputController;
    std::vector<GameObject*> sceneObjects;
};

#endif
