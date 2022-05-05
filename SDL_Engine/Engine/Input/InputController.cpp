#include "InputController.h"
#include "../GameManager.h"

InputController::InputController() {}

InputController::~InputController() {
}

void InputController::CreateAction(const std::string& actionName, int actionKey) {
    // Create bind to check if particular action is active
    namedActions.emplace(std::make_pair(actionKey, actionName));

    // Create bind to check if action is currently active
    activeEvents.emplace(std::make_pair(actionName, false));
}

// Adopted from here: https://stackoverflow.com/questions/2136998/using-a-stl-map-of-function-pointers
template<typename T>
void InputController::LinkAction(const std::string& actionName, const T& function) {
    // Create bind from key to function
    auto arguments = std::type_index(typeid(function));
    keyActions.emplace(std::make_pair(actionName, std::make_pair((KeyAction)function, arguments)));
}

template<typename T>
void InputController::LinkAction(const int actionKey, const T& function) {
    auto it = namedActions.find(actionKey);
    if (it != namedActions.end()) LinkAction((*it).second, function);
}

template<typename T, typename... Args>
void InputController::CallAction(const int key, Args&&... args) {
    auto it = keyActions.find(key);
    if (it == keyActions.end()) return;

    auto functionWithArgumentsPair = it->second;
    auto typeCastedFunction = reinterpret_cast<T(*)(Args ...)>(functionWithArgumentsPair.first);

    // compare the types are equal or not
    assert(functionWithArgumentsPair.second == std::type_index(typeid(typeCastedFunction)));

    return typeCastedFunction(std::forward<Args>(args)...);
}

void InputController::SetKeyActive(const int key, const bool newStatus) {
    auto it = activeKeys.find(key);
    if (it != activeKeys.end()) activeKeys.at(key) = newStatus;
}

void InputController::ProcessInput(const SDL_Event& inputEvent) const {
    switch (inputEvent.type) {
    case SDL_KEYDOWN:
        InputLogger::Instance().LogMessage("ASCII Key " + std::to_string(inputEvent.key.keysym.sym) + " was pressed!");
        break;

    case SDL_KEYUP:
        InputLogger::Instance().LogMessage("ASCII Key " + std::to_string(inputEvent.key.keysym.sym) + " was released!");
        break;

    case SDL_MOUSEBUTTONDOWN:
        InputLogger::Instance().LogMessage("Mouse hold!");
        break;

    case SDL_MOUSEBUTTONUP:
        InputLogger::Instance().LogMessage("Mouse release!");
        break;

    case SDL_QUIT:
        GameManager::Instance()->QuitTheGame();
        break;
    }
}