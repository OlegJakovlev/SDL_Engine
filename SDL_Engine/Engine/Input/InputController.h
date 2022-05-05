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
    InputController(const std::string& sceneName);
    virtual ~InputController();

    template<typename T>
    void AddAction(const std::string& actionName, const int actionKey, const T& function);

    template<typename T, typename... Args>
    void CallAction(const int key, Args&&... args);

    void SetKeyActive(const int key, const bool newStatus);
    void ProcessInput(const SDL_Event& inputEvent) const;

private:
    typedef void (*KeyAction)(void); // function pointer type

    std::unordered_map<int, std::pair<KeyAction, std::type_index>> keyActions; // Bind key to function with arguments
    std::unordered_map<int, bool> activeKeys; // Check if particular key is pressed
    std::unordered_map<std::string, int> namedActions; // Bind event name with key
};

#endif