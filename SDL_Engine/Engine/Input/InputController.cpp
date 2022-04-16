#include "InputController.h"
#include "../GameManager.h"

InputController::InputController() {
    // Initialize dictionary with all input buttons

}

InputController::~InputController() {
}

void InputController::ProcessInput(const SDL_Event& inputEvent) const {
    switch (inputEvent.type) {
    case SDL_KEYDOWN:
        std::printf("ASCII Key %i was pressed!", inputEvent.key.keysym.sym);
        break;
    case SDL_KEYUP:
        std::printf("ASCII Key %i was released!", inputEvent.key.keysym.sym);
        break;
    case SDL_MOUSEBUTTONDOWN:
        std::printf("Mouse hold!");
        break;
    case SDL_MOUSEBUTTONUP:
        std::printf("Mouse release!");
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