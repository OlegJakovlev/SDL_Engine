#pragma once

#ifndef InputConfigurator_H
#define InputConfigurator_H

#include "../Configurator.h"
#include "../../Input/InputController.h"

class InputConfigurator : public Configurator {
public:
    explicit InputConfigurator(const std::string& configPath);
    ~InputConfigurator();
    void LoadConfiguration() override;

    InputController* GetInputController();

private:
    InputController* inputController;
};

#endif