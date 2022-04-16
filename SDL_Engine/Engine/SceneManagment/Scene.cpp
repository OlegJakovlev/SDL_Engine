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

    for (GameObject::GameObject* gameobject : sceneObjects) {
        delete gameobject;
    }

    sceneObjects.clear();
}

void Scene::AddSceneObject(GameObject::GameObject* newObject) {
    sceneObjects.push_back(newObject);
}

const int Scene::GetID() {
    return ID;
}

const std::string& Scene::GetName() {
    return name;
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
