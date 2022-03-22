#include "Scene.h"

Scene::Scene(int newID, const std::string& newName) : ID(newID), name(newName) {
    gameLoop = new GameLoop();
    inputController = new InputController();
}

Scene::~Scene() {
    delete gameLoop;
    gameLoop = nullptr;

    delete inputController;
    inputController = nullptr;

    for (int gameObjectIndex = 0; gameObjectIndex < sceneObjects.size(); gameObjectIndex++) {
        delete sceneObjects[gameObjectIndex];
    }

    sceneObjects.clear();
}

void Scene::AddSceneObject(GameObject::GameObject* newObject) {
    sceneObjects.push_back(newObject);
}

const int Scene::GetID() {
    return ID;
}

GameLoop* Scene::GetGameLoop() {
    return gameLoop;
}

InputController* Scene::GetInputController() {
    return inputController;
}

std::vector<GameObject::GameObject*>& Scene::GetSceneObjectList() {
    return sceneObjects;
}
