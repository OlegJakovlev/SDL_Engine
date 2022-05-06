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

void InputController::LinkAction(const std::string& actionName, void* function) {
    //keyActions.emplace(std::make_pair(actionName, function));
}

void InputController::LinkAction(const int actionKey, void* function) {
    auto it = namedActions.find(actionKey);
    if (it != namedActions.end()) LinkAction((*it).second, function);
}

void InputController::CallAction(const std::string& actionName) {
    /*
    auto it = keyActions.find(actionName);
    if (it == keyActions.end()) return;

    // Execute linked function
    ((*it).second)();
    */
}

void InputController::CallAction(int key) {
    auto it = namedActions.find(key);
    if (it == namedActions.end()) return;

    CallAction((*it).second);
}

void InputController::SetEventActive(const std::string& eventName, const bool newStatus) {
    auto it = activeEvents.find(eventName);
    if (it != activeEvents.end()) activeEvents.at(eventName) = newStatus;
}

void InputController::ProcessInput(const SDL_Event& inputEvent) {
    switch (inputEvent.type) {
    case SDL_KEYDOWN:
        InputLogger::Instance().LogMessage("ASCII Key " + std::to_string(inputEvent.key.keysym.scancode) + " was pressed!");
        CallAction(inputEvent.key.keysym.scancode);
        break;

    case SDL_KEYUP:
        InputLogger::Instance().LogMessage("ASCII Key " + std::to_string(inputEvent.key.keysym.scancode) + " was released!");
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
