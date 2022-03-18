#include "Configurator.h"

Configurator::Configurator(const std::string& newConfigPath) : configPath(newConfigPath) {
}

void Configurator::SaveConfiguration() {
    FileWriter::WriteToFile(configPath, configuration.dump(), FileWriter::Mode::WRITE);
}

void Configurator::LoadConfiguration() {
    std::ifstream file(configPath);
    
    if (!file.is_open() || !file.good()) return;
    
    file >> configuration;
    file.close();
}
