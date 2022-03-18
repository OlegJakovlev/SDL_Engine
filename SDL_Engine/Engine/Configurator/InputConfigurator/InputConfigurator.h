#pragma once

#ifndef InputConfigurator_H
#define InputConfigurator_H

#include "../Configurator.h"

class InputConfigurator : public Configurator {
public:
    explicit InputConfigurator(const std::string& configPath);
};

#endif