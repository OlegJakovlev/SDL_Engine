#pragma once

#ifndef TextureConfigurator_H
#define TextureConfigurator_H

#include <filesystem>
#include "../Configurator.h"
#include "../../Locator/TextureLocator/TextureLocator.h"
#include "../../Service/TextureManager/RegularTextureManager/TextureManager.h"

class TextureConfigurator : public Configurator {
public:
    explicit TextureConfigurator(const std::string& texturesPath);
    ~TextureConfigurator();

    void LoadConfiguration() override;
};

#endif