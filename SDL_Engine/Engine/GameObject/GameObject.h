#pragma once

#ifndef GameObject_H
#define GameObject_H

#include <vector>
#include <string>
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
        void SetTransform(const Vector2::Vector2<int>& newTransform);
        void SetRotation(const Vector2::Vector2<float>& newRotation);
        void SetScale(const Vector2::Vector2<float>& newScale);
        void SetActive(bool newStatus);

        const int GetID() const;
        const std::string& GetName() const;
        const Vector2::Vector2<int>* GetTransform() const;
        const Vector2::Vector2<float>* GetRotation() const;
        const Vector2::Vector2<float>* GetScale() const;
        const std::vector<GameObject*>& GetChildObjects() const;
        const bool IsActive() const;

        // General object functions
        void SetParentObject(GameObject* newParent);
        const GameObject* GetParentObject();
        void AddChildObject(GameObject* newChildObject);
        const bool ShouldBeDeleted() const;
        
        void AddComponent(const std::string& componentName);
        IComponent* GetComponent(const std::string& componentName) const;

        // Debug functions
        void Print(int tabLevel = 0);

        // Game Loop
        void Update();
        void Render();

        // Delete object
        void Destroy();

    private:
        int ID;
        std::string name;

        Vector2::Vector2<int>* transform; // relative to its parent / world root object
        Vector2::Vector2<float>* rotation;
        Vector2::Vector2<float>* scale;

        std::unordered_map<std::string, IComponent*> components;
        
        GameObject* parentObject;
        std::vector<GameObject*> childObjects;
        
        bool active = true;
        bool dirtyFlag = true; // flag specifying if local position should be recalculated
        bool toBeDeleted = false;
    };

    void to_json(nlohmann::json& json, const GameObject* objectToConvert);
    void to_json(nlohmann::json& json, const GameObject& objectToConvert);
    void from_json(const nlohmann::json& json, GameObject& objectToConvert);
}

#endif