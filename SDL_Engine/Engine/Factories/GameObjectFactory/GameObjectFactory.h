#pragma once

#ifndef GameObjectFactory_H
#define GameObjectFactory_H

#include <fstream>
#include "../../GameObject/GameObject.h"

class GameObjectFactory {
public:
    ~GameObjectFactory();

    static GameObjectFactory* Instance();

    GameObject::GameObject* CreateGameObject();
    GameObject::GameObject* CreateGameObject(const std::string& name);
    GameObject::GameObject* CreateGameObject(nlohmann::json& config);

    GameObject::GameObject* CreateGameObjectFromFile(const std::string& filename);

private:
    GameObjectFactory() = default;

    static GameObjectFactory* sInstance;
    static int nextID;
};

#endif