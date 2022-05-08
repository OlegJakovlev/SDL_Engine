#include "ObjectPoolComponent.h"

ObjectPoolComponent::~ObjectPoolComponent() {
    for (auto& poolObject : pool) delete poolObject;
    pool.clear();
}

void ObjectPoolComponent::Init() {
    for (int i = 0; i < poolSize; i++) {
        GameObject::GameObject* newObject = GameObjectFactory::Instance()->CreateGameObject(objectConfiguration);
        pool.push_back(newObject);
    }
}

void ObjectPoolComponent::LoadConfig(const nlohmann::json& config) {
    poolSize = config.at("size").get<int>();
    objectConfiguration = config.at("config");
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
