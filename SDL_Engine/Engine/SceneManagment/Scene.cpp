#include "Scene.h"

Scene::Scene(int newID, const std::string& newName,
    const std::string& inputConfigFile,
    const std::string& texturesPath,
    const std::string& animationConfigFile) : ID(newID), name(newName) {

    gameLoop = new GameLoop();
    inputConfigurator = new InputConfigurator(inputConfigFile);
    textureConfigurator = new TextureConfigurator(texturesPath);
    animatorConfigurator = new AnimatorConfigurator(animationConfigFile);
}

Scene::~Scene() {
    delete gameLoop;
    gameLoop = nullptr;

    delete inputConfigurator;
    inputConfigurator = nullptr;

    delete textureConfigurator;
    textureConfigurator = nullptr;

    delete animatorConfigurator;
    animatorConfigurator = nullptr;

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

const int Scene::GetID() const {
    return ID;
}

const std::string& Scene::GetName() const {
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

void Scene::DeleteMarkedObjects() {
    std::vector<GameObject::GameObject*>::iterator it = sceneObjects.begin();
    for (; it != sceneObjects.end();) {
        if ((*it)->ShouldBeDeleted()) {
            GameObject::GameObject* tmp = *it;
            it = sceneObjects.erase(it);
            delete tmp;
        }
        else {
            (*it)->CheckChildsToBeDeleted();
            it++;
        }
    }
}

void Scene::Initialize() {
    // Load configurations
    inputConfigurator->LoadConfiguration();
    textureConfigurator->LoadConfiguration();
    animatorConfigurator->LoadConfiguration();

    // Initialize main binds
    inputConfigurator->Initialize();

    // Initialize scene objects with components
    for (GameObject::GameObject* sceneObject : sceneObjects) {
        InitializeRecursively(sceneObject);
    }

    // Initialize game loop
    gameLoop->Initialize(this);
    initialized = true;
}

void Scene::Reset() {
    // Reset keyboard state
    inputConfigurator->Reset();

    /* TODO: implement Reset for each component to avoid memory leak on initialization

    // Reset scene objects with components
    for (GameObject::GameObject* sceneObject : sceneObjects) {
        ResetRecursively(sceneObject);
    }

    initialized = false;
    */
}

void Scene::InitializeRecursively(GameObject::GameObject* rootObject) {
    rootObject->Initialize();

    for (auto& childObject : rootObject->GetChildObjects()) {
        InitializeRecursively(childObject);
    }
}

void Scene::ResetRecursively(GameObject::GameObject* rootObject) {
    rootObject->Reset();

    for (auto& childObject : rootObject->GetChildObjects()) {
        ResetRecursively(childObject);
    }
}
