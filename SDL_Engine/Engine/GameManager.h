#pragma once

#ifndef GameManager_H
#define GameManager_H

#include <SDL.h>
#include "Graphics/Graphics.h"
#include "Input/InputController.h"
#include "SceneManagment/SceneManager.h"

class GameManager {
public:
    static GameManager* Instance();
    void Init();
    void Run();
    static void Release();
    void QuitTheGame();

private:
    GameManager() = default;
    GameManager& operator=(const GameManager&) = delete;
    GameManager(const GameManager&) = delete;
    ~GameManager();

    static GameManager* sInstance;

    // Overall game state
    bool quit;
    Graphics* graphics;
    SDL_Event eventQueue;

    // Game managers
    SceneManager* sceneManager;
};

#endif
