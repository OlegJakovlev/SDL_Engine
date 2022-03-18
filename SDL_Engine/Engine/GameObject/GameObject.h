#pragma once

#ifndef GameObject_H
#define GameObject_H

#include <vector>
#include <string>
#include <algorithm>
#include "../Physics/Vector2.h"

class GameObject {
public:
    GameObject() = default;
    ~GameObject();

    // Setters / Getters
    Vector2<int> getTransform() const;
    Vector2<float> getRotation() const;
    Vector2<float> getScale() const;
    bool ShouldBeDeleted() const;

    // Game Loop
    void Update();
    void Render();

    // Delete object
    void Destroy();

private:
    int ID;
    std::string name;
    Vector2<int> transform;
    Vector2<float> rotation;
    Vector2<float> scale;

    std::vector<GameObject*> childObjects;
    bool dirtyFlag = true; // flag specifying if local position should be recalculated

    bool toBeDeleted;
};

#endif