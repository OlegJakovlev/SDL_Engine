#include "GameObject.h"

GameObject::~GameObject() {
    childObjects.clear();
}

Vector2<int> GameObject::getTransform() const {
    return transform;
}

Vector2<float> GameObject::getRotation() const {
    return rotation;
}

Vector2<float> GameObject::getScale() const {
    return scale;
}

void GameObject::Update() {
    //
}

void GameObject::Render() {
    //
}

void GameObject::Destroy() {
    toBeDeleted = true;

    if (childObjects.size() <= 0) return;

    std::for_each(childObjects.begin(), childObjects.end(), [](GameObject* childObject) {
        childObject->Destroy();
    });
}

bool GameObject::ShouldBeDeleted() const {
    return toBeDeleted;
}
