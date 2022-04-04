#include "InputConfigurator.h"

InputConfigurator::InputConfigurator(const std::string& configPath) : Configurator(configPath) {
}

void InputConfigurator::LoadConfiguration() {
	Configurator::LoadConfiguration();

	// Do we load only buttons? If not, how do we store binded actions?
	// Pointer to function?
}
