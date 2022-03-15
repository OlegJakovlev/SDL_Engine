#pragma once

#ifndef Scene_H
#define Scene_H

#include <vector>
#include "../GameObject/GameObject.h"

class Scene {
    std::vector<GameObject*> sceneObjects;
};

#endif
