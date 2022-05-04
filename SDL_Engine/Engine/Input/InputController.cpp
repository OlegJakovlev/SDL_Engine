#include "InputController.h"
#include "../GameManager.h"

InputController::InputController() {
}

InputController::InputController(const std::string& sceneName) {

}

InputController::~InputController() {
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

bool InputController::IsActionActive(const std::string& actionName) const {
    return true;
}