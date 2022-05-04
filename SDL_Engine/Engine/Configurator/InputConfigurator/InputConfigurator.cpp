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

	// Do we load only buttons? If not, how do we store binded actions?
	// Pointer to function?
}

InputController* InputConfigurator::GetInputController() {
	return inputController;
}
