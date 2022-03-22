#pragma once

#ifndef SceneConfigurator_H
#define SceneConfigurator_H

#include "../Configurator.h"
#include "../../SceneManagment/SceneManager.h"

class SceneConfigurator : public Configurator {
public:
    explicit SceneConfigurator(const std::string& newConfigPath);
    ~SceneConfigurator();
    void LoadConfiguration() override;

private:
    SceneManager* sceneManager;
};

#endif