#pragma once

#ifndef Configurator_H
#define Configurator_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class Configurator {
public:
    explicit Configurator(const std::string& newConfigPath);
    virtual ~Configurator();

    void SaveConfiguration();
    void LoadConfiguration();

protected:
    const std::string configPath;
    nlohmann::json configuration;
    std::vector<Configurator*> childConfigurators;
};

#endif