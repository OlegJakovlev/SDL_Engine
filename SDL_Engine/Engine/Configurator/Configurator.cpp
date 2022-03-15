#include "Configurator.h"

Configurator::Configurator(const std::string& newConfigPath) : configPath(newConfigPath)
{
}

Configurator::~Configurator() {
    childConfigurators.clear();
}

void Configurator::SaveConfiguration() {
}

void Configurator::LoadConfiguration() {
}
