#pragma once

#ifndef Configurator_H
#define Configurator_H

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../FileWriter/FileWriter.h"

class Configurator : public FileWriter {
public:
    explicit Configurator(const std::string& newConfigPath);
    virtual ~Configurator() = default;

    virtual void SaveConfiguration();
    virtual void LoadConfiguration();

protected:
    const std::string configPath;
    nlohmann::json configuration;
};

#endif