#pragma once

#ifndef InputController_H
#define InputController_H

#include <utility>
#include <unordered_map>
#include <string>
#include <SDL.h>
#include "../Logger/InputLogger/InputLogger.h"

class GameManager;

class InputController {
private:
    std::unordered_map<int, bool> keyBinds;

public:
    InputController();
    InputController(const std::string& sceneName);
    virtual ~InputController();

    bool IsActionActive(const std::string& actionName) const;
    void ProcessInput(const SDL_Event& inputEvent) const;
};

#endif