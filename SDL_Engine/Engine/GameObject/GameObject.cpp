#include "GameObject.h"

namespace GameObject {
    GameObject::GameObject(nlohmann::json& json) {
        SetID(json.at("ID").get<int>());
        SetName(json.at("name").get<std::string>());
        SetTransform(json.at("transform").get<Vector2::Vector2<int>>());
        SetRotation(json.at("rotation").get<Vector2::Vector2<float>>());
        SetScale(json.at("scale").get<Vector2::Vector2<float>>());
        SetComponents(json.at("components"));
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

    void GameObject::SetComponents(nlohmann::json& json) {
        for (auto& component : json) {
            AddComponent(component.at("name"), component.at("config"));
        }
    }

    void GameObject::SetActive(bool newStatus) {
        active = newStatus;
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

    const bool GameObject::IsActive() const {
        return active;
    }

    void GameObject::AddComponent(const std::string& componentName, const nlohmann::json& componentConfig) {
        // Create the component
        AbstractComponent* newComponent = ComponentFactory::Instance()->CreateComponent(componentName);
        
        // Link the component with gameobject
        newComponent->LinkWithObject(this);

        // Load component config
        newComponent->LoadConfig(componentConfig);

        // Save the component
        components.insert(std::pair<std::string, AbstractComponent*>(componentName, newComponent));
    }

    AbstractComponent* GameObject::GetComponent(const std::string& componentName) const {
        try {
            return components.at(componentName);
        }
        catch (std::out_of_range& oor) {
            return nullptr;
        }
    }

    void GameObject::Initialize() {
        UpdateGlobalTransform();
        
        for (auto& it : components) {
            it.second->Init();
        }
    }

    void GameObject::Update() {
        if (!active) return;

        // Update current object
        for (auto& component : components) {
            component.second->Update();
        }

        // Update child objects
        for (auto& child : childObjects) {
            child->Update();
        }
    }

    void GameObject::Render() {
        if (!active) return;

        // Update current object
        for (auto& component : components) {
            component.second->Render();
        }

        // Update child objects
        for (auto& child : childObjects) {
            child->Render();
        }
    }

    void GameObject::Destroy() {
        toBeDeleted = true;

        if (childObjects.size() <= 0) return;

        std::for_each(childObjects.begin(), childObjects.end(), [](GameObject* childObject) {
            childObject->Destroy();
        });
    }

    void GameObject::SetParentObject(GameObject* newParent) {
        parentObject = newParent;
    }

    const GameObject* GameObject::GetParentObject() {
        return parentObject;
    }

    void GameObject::AddChildObject(GameObject* newChildObject) {
        childObjects.push_back(newChildObject);
    }

    GameObject* GameObject::FindChildGameObjectByID(int searchableID) {
        GameObject* result = nullptr;
        result = RecursiveSearchByID(this, searchableID);
        return result;
    }

    GameObject* GameObject::FindChildGameObjectByName(const std::string& searchableName) {
        GameObject* result = nullptr;
        result = RecursiveSearchByName(this, searchableName);
        return result;
    }

    GameObject* GameObject::RecursiveSearchByID(GameObject* searchRoot, int searchableID) {
        GameObject* result = nullptr;

        if (searchRoot->ID == searchableID) return searchRoot;

        for (auto& childObject : searchRoot->childObjects) {
            result = RecursiveSearchByID(childObject, searchableID);

            if (result != nullptr) return result;
        }

        return nullptr;
    }

    GameObject* GameObject::RecursiveSearchByName(GameObject* searchRoot, const std::string& searchableName) {
        GameObject* result = nullptr;

        if (searchRoot->name == searchableName) return searchRoot;

        for (auto& childObject : searchRoot->childObjects) {
            result = RecursiveSearchByName(childObject, searchableName);

            if (result != nullptr) return result;
        }

        return nullptr;
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