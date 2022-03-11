#pragma once

#ifndef GameManager_H
#define GameManager_H

#include "./Graphics/Graphics.h"
#include <SDL.h>

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
    bool quit;
    Graphics* graphics;
    SDL_Event eventQueue;
};

#endif
