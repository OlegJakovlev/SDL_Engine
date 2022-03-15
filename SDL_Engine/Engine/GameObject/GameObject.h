#pragma once

#ifndef GameObject_H
#define GameObject_H

#include <vector>
#include <algorithm>

class GameObject {
public:
    GameObject() = default;
    ~GameObject();

    void Update();
    void Destroy();

private:
    std::vector<GameObject*> childObjects;
    bool toBeDeleted;
};

#endif