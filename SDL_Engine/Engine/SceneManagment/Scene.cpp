#include "Scene.h"

Scene::Scene() {
    gameLoop = new GameLoop();
    inputController = new InputController();
}

Scene::~Scene() {
    delete gameLoop;
    gameLoop = nullptr;

    delete inputController;
    inputController = nullptr;
}

GameLoop* Scene::GetGameLoop() {
    return gameLoop;
}

InputController* Scene::GetInputController() {
    return inputController;
}

std::vector<GameObject*>& Scene::GetSceneObjectList() {
    return sceneObjects;
}
