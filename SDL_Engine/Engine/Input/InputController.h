#pragma once

#ifndef InputController_H
#define InputController_H

#include <utility>
#include <unordered_map>
#include <typeindex>
#include <string>
#include <SDL.h>
#include <functional>
#include "../Logger/InputLogger/InputLogger.h"

class GameManager;

class InputController {
public:
    InputController();
    virtual ~InputController();

    void CreateAction(const std::string& actionName, int actionKey);

    void LinkAction(const std::string& actionName, std::function<void()> function);
    void LinkAction(int actionKey, std::function<void()> function);

    void CallAction(const std::string& actionName);
    void CallAction(int actionKey);

    void SetEventActive(const std::string& eventName, const bool newStatus);
    void SetEventActive(const int& eventButton, const bool newStatus);

    void ProcessInput(const SDL_Event& inputEvent);
    void ResetProcessedStatus();

private:
    std::unordered_map<int, std::string> namedActions; // Bind key with event name
    std::unordered_map<std::string, bool> activeEvents; // Check if particular event is activated
    std::unordered_map<std::string, std::function<void()>> keyActions; // Bind event name to function

    bool processed;
};

#endif