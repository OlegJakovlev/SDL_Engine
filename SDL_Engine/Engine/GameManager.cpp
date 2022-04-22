#include "GameManager.h"

GameManager* GameManager::sInstance = nullptr;

GameManager* GameManager::Instance() {
    if (sInstance == nullptr) sInstance = new GameManager();
    return sInstance;
}

void GameManager::Init(SceneManager* newSceneManager) {
    quit = false;
    graphics = Graphics::Instance();
    eventQueue = {};

    // Link game managers
    sceneManager = newSceneManager;

    Logger::Instance().LogMessage("Game Manager succesfully initialized!");
}

GameManager::~GameManager() {
    Graphics::Release();
    graphics = nullptr;
    sceneManager = nullptr;
}

void GameManager::Release() {
    delete sInstance;
    sInstance = nullptr;
}

void GameManager::Run() {
    Scene* currentScene = nullptr;

    while (!quit) {
        currentScene = sceneManager->GetCurrentScene();

        if (currentScene != nullptr) {
            // Run game loop on active scene
            currentScene->GetGameLoop()->Run(
                currentScene->GetInputController(),
                currentScene->GetSceneObjectList()
            );
        }
    }
}

void GameManager::QuitTheGame() {
    quit = true;
}

SceneManager* GameManager::GetSceneManager() {
    return sceneManager;
}
