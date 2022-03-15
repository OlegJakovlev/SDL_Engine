#pragma once

#ifndef GameManager_H
#define GameManager_H

#include <SDL.h>
#include "Graphics/Graphics.h"
#include "Input/InputController.h"
#include "Timer/Timer.h"

class GameManager {
public:
    static GameManager* Instance();
    void Run();
    static void Release();

private:
    GameManager();
    GameManager& operator=(const GameManager&) = delete;
    GameManager(const GameManager&) = delete;
    ~GameManager();

    static GameManager* sInstance;

    // Overall game state
    bool quit;
    Graphics* graphics;
    SDL_Event eventQueue;

    // Game loop
    Timer* timer;
    const float FIXED_DELTA_TIME = 0.01;
    const int MAX_PHYSICS_UPDATES = 5;
    double previousTime;
    double timeLag; // how far games' clock is behind real world
};

#endif
