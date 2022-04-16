#pragma once

#ifndef Scene_H
#define Scene_H

#include <vector>
#include "../GameObject/GameObject.h"
#include "../GameLoop/GameLoop.h"

class Scene {

public:
    Scene(int newID, const std::string& newName);
    ~Scene();

    void AddSceneObject(GameObject::GameObject* newObject);

    const int GetID();
    const std::string& GetName();

    GameLoop* GetGameLoop();
    InputController* GetInputController();
    std::vector<GameObject::GameObject*>& GetSceneObjectList();

private:
    const int ID;
    const std::string name;

    GameLoop* gameLoop;
    InputController* inputController;
    std::vector<GameObject::GameObject*> sceneObjects;
};

#endif
