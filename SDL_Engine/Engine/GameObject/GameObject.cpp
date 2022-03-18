#include "GameObject.h"

GameObject::~GameObject() {
    childObjects.clear();
}

Vector2<int> GameObject::GetPosition() const {
    return position;
}

Vector2<float> GameObject::GetRotation() const {
    return rotation;
}

Vector2<float> GameObject::GetScale() const {
    return scale;
}

void GameObject::Update() {
    //
}

void GameObject::Render(Graphics* graphics) {
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
