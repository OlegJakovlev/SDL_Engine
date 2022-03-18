#pragma once

#ifndef GameObject_H
#define GameObject_H

#include <vector>
#include <string>
#include <algorithm>
#include "../Physics/Vector2.h"
#include "../Graphics/Graphics.h"

class GameObject {
public:
    GameObject() = default;
    ~GameObject();

    // Setters / Getters
    Vector2<int> GetPosition() const;
    Vector2<float> GetRotation() const;
    Vector2<float> GetScale() const;
    bool ShouldBeDeleted() const;

    // Game Loop
    virtual void Update();
    virtual void Render(Graphics* graphics);

    // Delete object
    void Destroy();

protected:
    int ID;
    std::string name;
    Vector2<int> position;
    Vector2<float> rotation;
    Vector2<float> scale;

    std::vector<GameObject*> childObjects;
    bool dirtyFlag = true; // flag specifying if local position should be recalculated

    bool toBeDeleted;
};

#endif