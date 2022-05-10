#pragma once

#include "../AbstractComponent.h"
#include "../../Factories/GameObjectFactory/GameObjectFactory.h"

class ObjectPoolComponent : public AbstractComponent {
public:
    ~ObjectPoolComponent();

    void Init() override;
    void LoadConfig(const nlohmann::json& config) override;
    void Update() override;
    void Render() override;

    GameObject::GameObject* GetPoolObject();

private:
    int poolSize;
    nlohmann::json objectConfiguration;
    std::vector<GameObject::GameObject*> pool;
};

