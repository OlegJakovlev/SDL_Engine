#include "InputConfigurator.h"
#include <iostream>

InputConfigurator::InputConfigurator(const std::string& configPath) : Configurator(configPath) {
}

InputConfigurator::~InputConfigurator() {
	delete inputController;
	inputController = nullptr;
}

void InputConfigurator::LoadConfiguration() {
	Configurator::LoadConfiguration();

	inputController = new InputController();

	for (auto& typeOfControl : configuration.items()) {
		for (auto& keyBind : configuration.at(typeOfControl.key()).items()) {
			std::string actionName = keyBind.key();

			// http://www.wesnoth.org/devdocs/keyboard_8cpp_source.html
			SDL_Scancode bindKey = SDL_GetScancodeFromName(keyBind.value().get<std::string>().c_str());

			if (bindKey == SDL_SCANCODE_UNKNOWN) {
				InputLogger::Instance().LogError("Key Bind for " + actionName + " action is not valid!");
				continue;
			}

			inputController->CreateAction(actionName, bindKey);
		}
	}
}

// https://stackoverflow.com/questions/35189326/c-call-function-pointer-from-multiple-different-classes
void InputConfigurator::Initialize() {
	//inputController->LinkAction("toggleFullScreenMode", &ptfptr);
}

InputController* InputConfigurator::GetInputController() {
	return inputController;
}

void InputConfigurator::test() {
	std::cout << 1111111111111111 << "\n";
}