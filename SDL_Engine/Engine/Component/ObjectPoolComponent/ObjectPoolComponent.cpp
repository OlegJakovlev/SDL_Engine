#include "ObjectPoolComponent.h"

ObjectPoolComponent::~ObjectPoolComponent() {
    for (auto& poolObject : pool) delete poolObject;
    pool.clear();
}

void ObjectPoolComponent::Init() {
    for (int i = 0; i < poolSize; i++) {
        GameObject::GameObject* newObject = GameObjectFactory::Instance()->CreateGameObject(objectConfiguration);

        newObject->Initialize();
        newObject->SetActive(false);
        pool.push_back(newObject);
    }
}

void ObjectPoolComponent::LoadConfig(const nlohmann::json& config) {
    poolSize = config.at("size").get<int>();
    objectConfiguration = config.at("object");
}

void ObjectPoolComponent::Update() {
    for (auto& gameobject : pool) {
        gameobject->Update();
    }
}

void ObjectPoolComponent::Render() {
    for (auto& gameobject : pool) {
        gameobject->Render();
    }
}

GameObject::GameObject* ObjectPoolComponent::GetPoolObject() {
    for (int i = 0; i < poolSize; i++) {
        if (!pool[i]->IsActive()) {
            pool[i]->SetActive(true);
            return pool[i];
        }
    }

    return nullptr;
}
