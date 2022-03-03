#include "GameManager.h"

GameManager* GameManager::sInstance = nullptr;

GameManager* GameManager::Instance() {
    if (sInstance == nullptr) sInstance = new GameManager();
    return sInstance;
}

GameManager::GameManager() {
    quit = false;
    graphics = Graphics::Instance();
    eventQueue = {};
}

GameManager::~GameManager() {
    Graphics::Release();
    graphics = nullptr;
}

void GameManager::Release() {
    delete sInstance;
    sInstance = nullptr;
}

void GameManager::Run() {
    while (!quit) {
        while (SDL_PollEvent(&eventQueue) != 0) {
            if (eventQueue.type == SDL_QUIT) {
                quit = true;
            }

            graphics->Render();
        }
    }
}
