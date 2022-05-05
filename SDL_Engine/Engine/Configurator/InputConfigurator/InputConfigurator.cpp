#include "InputConfigurator.h"

InputConfigurator::InputConfigurator(const std::string& configPath) : Configurator(configPath) {
}

InputConfigurator::~InputConfigurator() {
	delete inputController;
	inputController = nullptr;
}

void InputConfigurator::LoadConfiguration() {
	Configurator::LoadConfiguration();

	inputController = new InputController();

	for (auto bind : configuration) {
		/*
		std::string actionName;

		SDL_Scancode bindKey = SDL_GetScancodeFromName();

		if (bindKey == SDL_SCANCODE_UNKNOWN) {
			InputLogger::Instance().LogError("");
			continue;
		}

		//inputController->AddAction(actionName, bindKey, &test);
		*/
	}
}

InputController* InputConfigurator::GetInputController() {
	return inputController;
}