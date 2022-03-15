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
    timer = new Timer();
}

GameManager::~GameManager() {
    Graphics::Release();
    graphics = nullptr;

    delete timer;
    timer = nullptr;
}

void GameManager::Release() {
    delete sInstance;
    sInstance = nullptr;
}

void GameManager::Run() {
    while (!quit) {
        double currentTime = timer->GetCurrentTime();
        double frameTime = currentTime - previousTime;
        int physicsUpdates = 0;

        // Update previous time
        previousTime = currentTime;

        // Accumulate time difference
        timeLag += frameTime;

        // Event Queue
        while (SDL_PollEvent(&eventQueue) != 0) {
            if (eventQueue.type == SDL_QUIT) {
                quit = true;
            }

            // Process Input
        }

        // Update
        while (timeLag >= FIXED_DELTA_TIME && physicsUpdates < MAX_PHYSICS_UPDATES) {
            physicsUpdates++;
            //update();
            timeLag -= FIXED_DELTA_TIME;
            currentTime += FIXED_DELTA_TIME;
        }

        // Render
        //graphics->Render(timeLag / FIXED_DELTA_TIME);
    }
}
