#pragma once

#ifndef ImageComponent_H
#define ImageComponent_H

#include <SDL_image.h>
#include "../AbstractComponent.h"
#include "../../Logger/GraphicsLogger/GraphicsLogger.h"

class ImageComponent : public AbstractComponent {
public:
    ~ImageComponent();

    void Init() override;
    void LoadConfig(const nlohmann::json& config) override;
    void Render() override;

private:
    std::string pathToImage;
    SDL_Texture* texture;
};

#endif