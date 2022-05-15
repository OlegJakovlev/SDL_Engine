#pragma once

#ifndef InputConfigurator_H
#define InputConfigurator_H

#include "../Configurator.h"
#include "../../Input/InputController.h"
#include "../../Graphics/Graphics.h"

class GameManager;

class InputConfigurator : public Configurator {
public:
    explicit InputConfigurator(const std::string& configPath);
    ~InputConfigurator();
    
    void LoadConfiguration() override;
    void Initialize();
    void Reset();

    InputController* GetInputController();

private:
    InputController* inputController;
};

#endif