#include "InputController.h"
#include "../GameManager.h"

InputController::InputController() {
}

InputController::InputController(const std::string& sceneName) {

}

InputController::~InputController() {
}

// Adopted from here: https://stackoverflow.com/questions/2136998/using-a-stl-map-of-function-pointers
template<typename T>
void InputController::AddAction(const std::string& actionName, const int actionKey, const T& function) {
    // Create bind from key to function
    auto arguments = std::type_index(typeid(function));
    keyActions.emplace(std::make_pair(actionKey, std::make_pair((KeyAction)function, arguments)));

    // Create bind to check if key is currently pressed
    activeKeys.emplace(std::make_pair(actionKey, false));

    // Create bind to check if particular action is active
    namedActions.emplace(std::make_pair(actionName, actionKey));
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