#include "ObjectPoolComponent.h"

ObjectPoolComponent::~ObjectPoolComponent() {
    pool.clear();
}

void ObjectPoolComponent::Init() {
    for (int i = 0; i < poolSize; i++) {
        GameObject::GameObject* newObject = GameObjectFactory::Instance()->CreateGameObject(objectConfiguration);

        newObject->Initialize();
        newObject->SetActive(false);

        pool.push_back(newObject);

        objectLinkedTo->AddChildObject(newObject);
        newObject->SetParentObject(objectLinkedTo);
    }
}

void ObjectPoolComponent::LoadConfig(const nlohmann::json& config) {
    poolSize = config.at("size").get<int>();
    objectConfiguration = config.at("object");
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
