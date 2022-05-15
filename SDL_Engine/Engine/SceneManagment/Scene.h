#pragma once

#ifndef Scene_H
#define Scene_H

#include <vector>
#include "../GameObject/GameObject.h"
#include "../GameLoop/GameLoop.h"
#include "../Configurator/InputConfigurator/InputConfigurator.h"
#include "../Configurator/TextureConfigurator/TextureConfigurator.h"
#include "../Configurator/AnimatorConfigurator/AnimatorConfigurator.h"

class Scene {

public:
    Scene(int newID,
        const std::string& newName,
        const std::string& inputConfigFile,
        const std::string& texturesPath,
        const std::string& animationConfigFile
    );
    ~Scene();

    void Initialize();
    void Reset();

    void AddSceneObject(GameObject::GameObject* newObject);
    GameObject::GameObject* GetSceneObjectByID(int objectID);
    GameObject::GameObject* GetSceneObjectByName(std::string objectName);

    const int GetID() const;
    const std::string& GetName() const;

    GameLoop* GetGameLoop();
    InputConfigurator* GetInputConfigurator();
    std::vector<GameObject::GameObject*>& GetSceneObjectList();
    bool IsInitialized();

    void DeleteMarkedObjects();

private:
    void InitializeRecursively(GameObject::GameObject* rootObject);
    void ResetRecursively(GameObject::GameObject* rootObject);

    const int ID;
    const std::string name;

    GameLoop* gameLoop;
    
    InputConfigurator* inputConfigurator;
    TextureConfigurator* textureConfigurator;
    AnimatorConfigurator* animatorConfigurator;

    std::vector<GameObject::GameObject*> sceneObjects;

    bool initialized = false;
};

#endif
