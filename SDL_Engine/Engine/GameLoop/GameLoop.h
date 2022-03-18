#pragma once

#ifndef GameLoop_H
#define GameLoop_H

#include <vector>
#include "../GameObject/GameObject.h"
#include "../Timer/Timer.h"
#include "../Graphics/Graphics.h"
#include "../Input/InputController.h"

class GameLoop {
public:
    GameLoop();
    ~GameLoop();

    void Run(Graphics* graphics, InputController* input, std::vector<GameObject*>& sceneObjects);

private:
    const double FIXED_DELTA_TIME = 0.01;
    const int MAX_PHYSICS_UPDATES = 5;
    
    Timer* timer;
    double previousTime;
    double timeLag; // how far games' clock is behind real world

    void Input(const InputController* input) const;
    void Update(std::vector<GameObject*>& sceneObjects) const;
    void Render(Graphics* graphics) const;
};

#endif