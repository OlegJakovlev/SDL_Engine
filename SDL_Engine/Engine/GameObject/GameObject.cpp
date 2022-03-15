#include "GameObject.h"

GameObject::~GameObject() {
    childObjects.clear();
}

void GameObject::Update() {
}

void GameObject::Destroy() {
    toBeDeleted = true;

    if (childObjects.size() <= 0) return;

    std::for_each(childObjects.begin(), childObjects.end(), [](GameObject* childObject) {
        childObject->Destroy();
    });
}
