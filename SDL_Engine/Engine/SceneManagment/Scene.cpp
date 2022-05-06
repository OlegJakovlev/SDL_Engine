#include "Scene.h"

Scene::Scene(int newID, const std::string& newName, const std::string& inputConfigFile) : ID(newID), name(newName) {
    gameLoop = new GameLoop();
    inputConfigurator = new InputConfigurator(inputConfigFile);
}

Scene::~Scene() {
    delete gameLoop;
    gameLoop = nullptr;

    delete inputConfigurator;
    inputConfigurator = nullptr;

    for (GameObject::GameObject* gameobject : sceneObjects) {
        delete gameobject;
    }

    sceneObjects.clear();
}

void Scene::AddSceneObject(GameObject::GameObject* newObject) {
    sceneObjects.push_back(newObject);
}

GameObject::GameObject* Scene::GetSceneObjectByID(int objectID) {
    GameObject::GameObject* result;

    for (GameObject::GameObject* sceneObject : sceneObjects) {
        if (sceneObject->GetID() == objectID) return sceneObject;

        // TODO: Replace this with binary search

        // Check recursively child objects
        result = sceneObject->FindChildGameObjectByID(objectID);
        if (result != nullptr) return result;
    }

    return nullptr;
}

GameObject::GameObject* Scene::GetSceneObjectByName(std::string objectName) {
    GameObject::GameObject* result;

    for (GameObject::GameObject* sceneObject : sceneObjects) {
        if (sceneObject->GetName() == objectName) return sceneObject;

        // Check recursively child objects
        result = sceneObject->FindChildGameObjectByName(objectName);
        if (result != nullptr) return result;
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

InputConfigurator* Scene::GetInputConfigurator() {
    return inputConfigurator;
}

std::vector<GameObject::GameObject*>& Scene::GetSceneObjectList() {
    return sceneObjects;
}

bool Scene::IsInitialized() {
    return initialized;
}

void Scene::Initialize() {
    // Load input configuration and initialize main binds
    inputConfigurator->LoadConfiguration();
    inputConfigurator->Initialize();

    // Initialize scene objects with components
    for (GameObject::GameObject* sceneObject : sceneObjects) {
        InitializeRecursively(sceneObject);
    }

    // Initialize game loop
    gameLoop->Initialize(this);
    initialized = true;
}

void Scene::InitializeRecursively(GameObject::GameObject* rootObject) {
    rootObject->Initialize();

    for (auto& childObject : rootObject->GetChildObjects()) {
        InitializeRecursively(childObject);
    }
}
