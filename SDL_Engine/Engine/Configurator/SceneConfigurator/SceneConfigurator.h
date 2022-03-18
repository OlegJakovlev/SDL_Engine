#pragma once

#ifndef SceneConfigurator_H
#define SceneConfigurator_H

#include "../Configurator.h"

class SceneConfigurator : public Configurator {
public:
    explicit SceneConfigurator(const std::string& newConfigPath);
    void LoadConfiguration() override;
};

#endif