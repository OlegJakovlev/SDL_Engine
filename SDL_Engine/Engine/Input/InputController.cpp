#include "InputController.h"
#include "../GameManager.h"

InputController::InputController() {
}

InputController::~InputController() {
}

void InputController::ProcessInput(const SDL_Event& inputEvent) const {
    switch (inputEvent.type) {
    case SDL_KEYDOWN:
        break;
    case SDL_KEYUP:
        break;
    case SDL_MOUSEBUTTONDOWN:
        break;
    case SDL_MOUSEBUTTONUP:
        break;
    case SDL_QUIT:
        GameManager::Instance()->QuitTheGame();
        break;
    }
}

bool InputController::IsActionActive(const std::string& actionName) const {
    // Check if action bind exists
    //if ((binds.find(actionName)) == binds.end()) return false;

    return true;
}