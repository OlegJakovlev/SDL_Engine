#pragma once

#ifndef GameObject_H
#define GameObject_H

#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <iostream>
#include "../Physics/Vector2.h"
#include "../Factories/ComponentFactory/ComponentFactory.h"

namespace GameObject {
    class GameObject {
    public:
        GameObject(nlohmann::json& json);
        GameObject(int newID, const std::string& newName);
        ~GameObject();

        // Setters / Getters
        void SetID(const int newID);
        void SetName(const std::string& newName);
        void SetLocalPosition(const Vector2::Vector2<int>& newTransform);
        void SetGlobalPosition(const Vector2::Vector2<int>& newTransform);
        void SetRotation(const float newRotation);
        void SetScale(const Vector2::Vector2<int>& newScale);
        void SetLayer(const int newLayer);
        void SetComponents(nlohmann::json& json);
        void SetActive(bool newStatus);
        void Deactivate();

        const int GetID() const;
        const std::string& GetName() const;
        const Vector2::Vector2<int>* GetLocalPosition() const;
        const Vector2::Vector2<int>* GetGlobalPosition() const;
        const float GetRotation() const;
        const Vector2::Vector2<int>* GetScale() const;
        const std::vector<GameObject*>& GetChildObjects() const;
        const std::bitset<4> GetLayer() const;
        const bool IsActive() const;

        // General object functions
        void SetParentObject(GameObject* newParent);
        const GameObject* GetParentObject();
        void AddChildObject(GameObject* newChildObject);
        const bool ShouldBeDeleted() const;

        GameObject* FindChildGameObjectByID(int searchableID);
        GameObject* FindChildGameObjectByName(const std::string& searchableName);
        
        void UpdateGlobalTransform();

        void AddComponent(const std::string& componentName, const nlohmann::json& componentConfig);
        AbstractComponent* GetComponent(const std::string& componentName) const;

        // Debug functions
        void Print(int tabLevel = 0);

        // Game Loop
        void Initialize();
        void Update();
        void Render();
        void Destroy();

        void CheckChildsToBeDeleted();

    private:
        GameObject* RecursiveSearchByID(GameObject* searchRoot, int searchableID);
        GameObject* RecursiveSearchByName(GameObject* searchRoot, const std::string& searchableName);

        int ID;
        std::string name;

        Vector2::Vector2<int>* localPosition; // relative to its parent / world root object
        Vector2::Vector2<int>* globalPosition;
        float rotation;
        Vector2::Vector2<int>* scale;

        std::bitset<4> layer;

        std::unordered_map<std::string, AbstractComponent*> components;

        GameObject* parentObject;
        std::vector<GameObject*> childObjects;

        bool active = true;
        bool dirtyFlag = true; // flag specifying if rerender should happen because of object position update
        bool toBeDeleted = false;
    };

    void to_json(nlohmann::json& json, const GameObject* objectToConvert);
    void to_json(nlohmann::json& json, const GameObject& objectToConvert);
    void from_json(const nlohmann::json& json, GameObject& objectToConvert);
}

#endif