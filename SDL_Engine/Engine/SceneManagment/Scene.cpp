#include "Scene.h"

Scene::Scene(int newID, const std::string& newName) : ID(newID), name(newName) {
    inputController = new InputController();
    gameLoop = new GameLoop();
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

GameObject::GameObject* Scene::GetSceneObjectByID(int objectID) {
    for (GameObject::GameObject* sceneObject : sceneObjects) {
        if (sceneObject->GetID() == objectID) return sceneObject;

        // Replace this with binary search
        for (GameObject::GameObject* childSceneObject : sceneObject->GetChildObjects()) {
            if (childSceneObject->GetID() == objectID) return childSceneObject;
        }
    }

    return nullptr;
}

GameObject::GameObject* Scene::GetSceneObjectByName(std::string objectName) {
    for (GameObject::GameObject* sceneObject : sceneObjects) {
        if (sceneObject->GetName() == objectName) return sceneObject;

        for (GameObject::GameObject* childSceneObject : sceneObject->GetChildObjects()) {
            if (childSceneObject->GetName() == objectName) return childSceneObject;
        }
    }
    
    return nullptr;
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

void Scene::Initialize() {
    // Initialize game loop
    gameLoop->Initialize(this);
}
