#include "GameObject.h"

namespace GameObject {
    GameObject::GameObject(nlohmann::json& json) {
        SetID(json.at("ID").get<int>());
        SetName(json.at("name").get<std::string>());
        SetLocalPosition(json.at("position").get<Vector2::Vector2<int>>());
        SetRotation(json.at("rotation").get<float>());
        SetScale(json.at("scale").get<Vector2::Vector2<int>>());
        SetLayer(json.at("layer"));
        SetComponents(json.at("components"));
    }

    GameObject::GameObject(int newID, const std::string& newName) {
        ID = newID;
        name = newName;
        localPosition = nullptr;
        globalPosition = nullptr;
        rotation = 0;
        scale = nullptr;
        layer = 8;
    }

    GameObject::~GameObject() {
        delete localPosition;
        localPosition = nullptr;

        delete globalPosition;
        globalPosition = nullptr;

        delete scale;
        scale = nullptr;

        // Destruct all components
        for (auto& componentEntry : components) {
            delete componentEntry.second;
        }

        components.clear();

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

    void GameObject::SetLocalPosition(const Vector2::Vector2<int>& newTransform) {
        delete localPosition;
        localPosition = new Vector2::Vector2<int>(newTransform);
    }

    void GameObject::SetGlobalPosition(const Vector2::Vector2<int>& newTransform) {
        delete globalPosition;
        globalPosition = new Vector2::Vector2<int>(newTransform);
    }

    void GameObject::SetRotation(const float newRotation) {
        rotation = newRotation;
    }

    void GameObject::SetScale(const Vector2::Vector2<int>& newScale) {
        delete scale;
        scale = new Vector2::Vector2<int>(newScale);
    }

    void GameObject::SetLayer(const int newLayer) {
        layer = std::bitset<4>(newLayer);
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

    const Vector2::Vector2<int>* GameObject::GetLocalPosition() const {
        return localPosition;
    }

    const Vector2::Vector2<int>* GameObject::GetGlobalPosition() const {
        return globalPosition;
    }

    const float GameObject::GetRotation() const {
        return rotation;
    }

    const Vector2::Vector2<int>* GameObject::GetScale() const {
        return scale;
    }

    const std::vector<GameObject*>& GameObject::GetChildObjects() const {
        return childObjects;
    }

    const std::bitset<4> GameObject::GetLayer() const {
        return layer;
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
        if (components.find(componentName) == components.end()) return nullptr;
        return components.at(componentName);
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

        // Render current object
        for (auto& component : components) {
            component.second->Render();
        }

        // Render child objects
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
        printf("%sTransform: %d, %d\n", tabs.c_str(), localPosition->x, localPosition->y);
        printf("%sRotation: %f\n", tabs.c_str(), rotation);
        printf("%sScale: %d, %d\n", tabs.c_str(), scale->x, scale->y);

        if (childObjects.empty()) return;
        printf("%sChild Game Objects:\n", tabs.c_str());

        for (GameObject* object : childObjects) {
            object->Print(tabLevel + 1);
            printf("\n");
        }
    }

    void GameObject::UpdateGlobalTransform() {
        delete globalPosition;

        // Check if parent object exists
        Vector2::Vector2<int> parentPosition = (parentObject == nullptr) ? Vector2::Vector2<int>(0, 0) : *(parentObject->localPosition);
        globalPosition = new Vector2::Vector2<int>(*localPosition + parentPosition);

        for (auto& child : childObjects) {
            child->UpdateGlobalTransform();
        }

        // Object should be rerendered
        dirtyFlag = true;
    }

    void to_json(nlohmann::json& json, const GameObject& objectToConvert) {
        json = nlohmann::json {
            {"ID", objectToConvert.GetID()},
            {"name", objectToConvert.GetName()},
            {"transform", *objectToConvert.GetLocalPosition()},
            {"rotation", objectToConvert.GetRotation()},
            {"scale", *objectToConvert.GetScale()},
            {"childObjects", objectToConvert.GetChildObjects()}
        };
    }

    void to_json(nlohmann::json& json, const GameObject* objectToConvert) {
        json = nlohmann::json {
            {"ID", objectToConvert->GetID()},
            {"name", objectToConvert->GetName()},
            {"transform", *objectToConvert->GetLocalPosition()},
            {"rotation", objectToConvert->GetRotation()},
            {"scale", *objectToConvert->GetScale()},
            {"childObjects", objectToConvert->GetChildObjects()}
        };
    }
}