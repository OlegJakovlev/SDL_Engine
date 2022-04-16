#pragma once

#ifndef GameLoop_H
#define GameLoop_H

#include <vector>
#include "../GameObject/GameObject.h"
#include "../Timer/Timer.h"
#include "../Graphics/Graphics.h"
#include "../Input/InputController.h"
#include "../Factories/GameObjectFactory/GameObjectFactory.h"

class GameLoop {
public:
    GameLoop();
    ~GameLoop();

    void Run(InputController* input, std::vector<GameObject::GameObject*>& sceneObjects);

private:
    const double SECONDS_PER_UPDATE = 0.016666; // 60 FPS
    const int MAX_PHYSICS_UPDATES = 120; // FPS * 2
    
    Timer* timer;
    double previousTime = 0;
    double timeLag = 0; // how far games' clock is behind real world

    const std::string statsViewConfigPath = "./Resources/Configurations/GameLoop/example.json";
    GameObject::GameObject* statsView; // game loop visual info

    void Input(const InputController* input) const;
    void Update(std::vector<GameObject::GameObject*>& sceneObjects) const;
};

#endif