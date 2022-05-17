#pragma once

#ifndef GameLoop_H
#define GameLoop_H

#include <vector>
#include "../GameObject/GameObject.h"
#include "../Timer/Timer.h"
#include "../Graphics/Graphics.h"
#include "../Input/InputController.h"
#include "../Factories/GameObjectFactory/GameObjectFactory.h"
#include "../../CustomScripts/GameLoopView.h"

class Scene;

class GameLoop {
public:
    GameLoop();
    ~GameLoop();

    void Initialize(Scene* masterScene);
    void Run(InputController* input, std::vector<GameObject::GameObject*>& sceneObjects);

    const Timer& GetTimer();

    void ToggleInput();
    void ToggleUpdate();
    void ToggleRender();

private:
    void DeleteMarkedObjects(std::vector<GameObject::GameObject*>& sceneObjects);

    const double SECONDS_PER_INPUT = 0.05;
    const double SECONDS_PER_UPDATE = 0.03333; // 60 FPS
    const int MAX_PHYSICS_UPDATES = 60; // FPS * 2

    Timer* timer;
    double previousTime = 0;
    double updateLag = 0;
    double inputLag = 0;

    // Performance
    double inputTime = 0;
    double updateTime = 0;
    double renderTime = 0;

    GameLoopView* gameStatsView;

    bool inputActive = true;
    bool updateActive = true;
    bool renderActive = true;

    void Input(InputController* input);
    void Update(std::vector<GameObject::GameObject*>& sceneObjects);
};

#endif