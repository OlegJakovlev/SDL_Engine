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
    GameLoop(Scene* linkTo);
    ~GameLoop();

    void Initialize();
    void Run(InputController* input, std::vector<GameObject::GameObject*>& sceneObjects);

private:
    const double SECONDS_PER_UPDATE = 0.016666; // 60 FPS
    const int MAX_PHYSICS_UPDATES = 120; // FPS * 2
    
    Scene* linkedTo;

    Timer* timer;
    double previousTime = 0;
    double timeLag = 0; // how far games' clock is behind real world

    double inputTime;
    double updateTime;
    double renderTime;

    GameLoopView* gameStatsView;

    void Input(const InputController* input) const;
    void Update(std::vector<GameObject::GameObject*>& sceneObjects) const;
};

#endif