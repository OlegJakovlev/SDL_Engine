#include "GameManager.h"

GameManager* GameManager::sInstance = nullptr;

GameManager* GameManager::Instance() {
    if (sInstance == nullptr) sInstance = new GameManager();
    return sInstance;
}

void GameManager::Init() {
    quit = false;
    graphics = Graphics::Instance();
    eventQueue = {};

    // Create game managers
    sceneManager = new SceneManager();
}

GameManager::~GameManager() {
    Graphics::Release();
    graphics = nullptr;

    delete sceneManager;
    sceneManager = nullptr;
}

void GameManager::Release() {
    delete sInstance;
    sInstance = nullptr;
}

void GameManager::Run() {
    Scene* currentScene;

    while (!quit) {
        currentScene = sceneManager->GetCurrentScene();

        // Run game loop on active scene
        currentScene->GetGameLoop()->Run(
            graphics,
            currentScene->GetInputController(),
            currentScene->GetSceneObjectList()
        );
    }
}

void GameManager::QuitTheGame() {
    quit = true;
}