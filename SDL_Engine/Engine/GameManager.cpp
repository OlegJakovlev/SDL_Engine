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

    GameData::Release();
}

void GameManager::Run() {
    Scene* currentScene = nullptr;

    while (!quit) {
        currentScene = sceneManager->GetCurrentScene();

        // Initialize all the gameObjects with all the components
        if (!currentScene->IsInitialized()) currentScene->Initialize();

        // Run game loop on active scene
        if (currentScene != nullptr) {
            currentScene->GetGameLoop()->Run(
                currentScene->GetInputConfigurator()->GetInputController(),
                currentScene->GetSceneObjectList()
            );
        }

        // Delete inactive
        currentScene->DeleteMarkedObjects();
    }
}

void GameManager::QuitTheGame() {
    quit = true;
}

SceneManager* GameManager::GetSceneManager() {
    return sceneManager;
}
