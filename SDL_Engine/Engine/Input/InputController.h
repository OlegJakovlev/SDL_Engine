#pragma once

#ifndef InputController_H
#define InputController_H

#include <utility>
#include <unordered_map>
#include <typeindex>
#include <string>
#include <SDL.h>
#include "../Logger/InputLogger/InputLogger.h"

class GameManager;

class InputController {
public:
    InputController();
    virtual ~InputController();

    void CreateAction(const std::string& actionName, int actionKey);

    template<typename T>
    void LinkAction(const std::string& actionName, const T& function);

    template<typename T>
    void LinkAction(const int actionKey, const T& function);

    template<typename T, typename... Args>
    void CallAction(const int actionKey, Args&&... args);

    void SetKeyActive(const int actionKey, const bool newStatus);
    void ProcessInput(const SDL_Event& inputEvent) const;

private:
    typedef void (*KeyAction)(void); // function pointer type

    std::unordered_map<int, std::string> namedActions; // Bind key with event name
    std::unordered_map<std::string, bool> activeEvents; // Check if particular event is activated
    std::unordered_map<std::string, std::pair<KeyAction, std::type_index>> keyActions; // Bind event name to function with arguments

};

#endif