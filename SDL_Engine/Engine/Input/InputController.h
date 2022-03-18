#pragma once

#ifndef InputController_H
#define InputController_H

#include <utility>
#include <unordered_map>
#include <set>
#include <string>
#include <iostream>
#include <SDL.h>

class GameManager;

class InputController {
private:
    std::unordered_map<int, std::string> keyBindsToEventName;
    std::set<std::string> activeEvents;

public:
    InputController();
    virtual ~InputController();

    bool IsActionActive(const std::string& actionName) const;
    void ProcessInput(const SDL_Event& inputEvent) const;
};

#endif