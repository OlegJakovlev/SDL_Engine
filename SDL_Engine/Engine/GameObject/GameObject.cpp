#include "GameObject.h"

namespace GameObject {
    GameObject::GameObject(nlohmann::json& json) {
        SetID(json.at("ID").get<int>());
        SetName(json.at("name").get<std::string>());
        SetTransform(json.at("transform").get<Vector2::Vector2<int>>());
        SetRotation(json.at("rotation").get<Vector2::Vector2<float>>());
        SetScale(json.at("scale").get<Vector2::Vector2<float>>());

        if (json.at("childObjects").empty()) return;

        // Construct child objects
        for (auto it : json.at("childObjects")) {
            AddChildObject(new GameObject(it));
        }
    }

    GameObject::GameObject(int newID, const std::string& newName) {
        ID = newID;
        name = newName;
        transform = nullptr;
        rotation = nullptr;
        scale = nullptr;
    }

    GameObject::~GameObject() {
        delete transform;
        transform = nullptr;

        delete rotation;
        rotation = nullptr;

        delete scale;
        scale = nullptr;

        // Destruct all child objects
        for (int childIndex = 0; childIndex < childObjects.size(); childIndex++) {
            delete childObjects[childIndex];
        }

        childObjects.clear();
    }

    void GameObject::SetID(const int newID) {
        ID = newID;
    }

    void GameObject::SetName(const std::string& newName) {
        name = newName;
    }

    void GameObject::SetTransform(const Vector2::Vector2<int>& newTransform) {
        transform = new Vector2::Vector2<int>(newTransform);
    }

    void GameObject::SetRotation(const Vector2::Vector2<float>& newRotation) {
        rotation = new Vector2::Vector2<float>(newRotation);
    }

    void GameObject::SetScale(const Vector2::Vector2<float>& newScale) {
        scale = new Vector2::Vector2<float>(newScale);
    }

    const int GameObject::GetID() const {
        return ID;
    }

    const std::string& GameObject::GameObject::GetName() const {
        return name;
    }

    const Vector2::Vector2<int>* GameObject::GetTransform() const {
        return transform;
    }

    const Vector2::Vector2<float>* GameObject::GetRotation() const {
        return rotation;
    }

    const Vector2::Vector2<float>* GameObject::GetScale() const {
        return scale;
    }

    const std::vector<GameObject*>& GameObject::GetChildObjects() const {
        return childObjects;
    }

    void GameObject::Update() {
        // Update current object
        std::for_each(components.begin(), components.end(), [](IComponent* component) {
            component->Update();
        });

        // Update child objects
        std::for_each(childObjects.begin(), childObjects.end(), [](GameObject* child) {
            child->Update();
        });
    }

    void GameObject::Render() {
        // Render current object
        std::for_each(components.begin(), components.end(), [](IComponent* component) {
            component->Render();
        });

        // Render child objects
        std::for_each(childObjects.begin(), childObjects.end(), [](GameObject* child) {
            child->Render();
        });
    }

    void GameObject::Destroy() {
        toBeDeleted = true;

        if (childObjects.size() <= 0) return;

        std::for_each(childObjects.begin(), childObjects.end(), [](GameObject* childObject) {
            childObject->Destroy();
        });
    }

    void GameObject::AddChildObject(GameObject* newChildObject) {
        childObjects.push_back(newChildObject);
    }

    const bool GameObject::ShouldBeDeleted() const {
        return toBeDeleted;
    }

    void GameObject::Print(int tabLevel) {
        std::string tabs = "";
        for (int i = 0; i < tabLevel; i++) tabs += "\t";

        printf("%sID:%d\n", tabs.c_str(), ID);
        printf("%sName: % s\n", tabs.c_str(), name.c_str());
        printf("%sTransform: %d, %d\n", tabs.c_str(), transform->GetX(), transform->GetY());
        printf("%sRotation: %f, %f\n", tabs.c_str(), rotation->GetX(), rotation->GetY());
        printf("%sScale: %f, %f\n", tabs.c_str(), scale->GetX(), scale->GetY());

        if (childObjects.empty()) return;
        printf("%sChild Game Objects:\n", tabs.c_str());

        for (GameObject* object : childObjects) {
            object->Print(tabLevel + 1);
            printf("\n");
        }
    }

    void to_json(nlohmann::json& json, const GameObject& objectToConvert) {
        json = nlohmann::json {
            {"ID", objectToConvert.GetID()},
            {"name", objectToConvert.GetName()},
            {"transform", *objectToConvert.GetTransform()},
            {"rotation", *objectToConvert.GetRotation()},
            {"scale", *objectToConvert.GetScale()},
            {"childObjects", objectToConvert.GetChildObjects()}
        };
    }

    void to_json(nlohmann::json& json, const GameObject* objectToConvert) {
        json = nlohmann::json {
            {"ID", objectToConvert->GetID()},
            {"name", objectToConvert->GetName()},
            {"transform", *objectToConvert->GetTransform()},
            {"rotation", *objectToConvert->GetRotation()},
            {"scale", *objectToConvert->GetScale()},
            {"childObjects", objectToConvert->GetChildObjects()}
        };
    }
}