#include "Scene.h"
#include "../../TestRectangle.h"

Scene::Scene() {
    gameLoop = new GameLoop();
    inputController = new InputController();

    TestRectangle* a = new TestRectangle();
    sceneObjects.push_back(a);
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
