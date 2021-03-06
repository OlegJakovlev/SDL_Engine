#pragma once

#ifndef ImageComponent_H
#define ImageComponent_H

#include <SDL_image.h>
#include "../AbstractComponent.h"
#include "../../Logger/GraphicsLogger/GraphicsLogger.h"
#include "../../Locator/TextureLocator/TextureLocator.h"

class ImageComponent : public AbstractComponent {
public:
    ~ImageComponent();

    void Init() override;
    void LoadConfig(const nlohmann::json& config) override;
    void Render() override;

    SDL_Texture* GetTexture() const;
    void SetTexture(SDL_Texture* newTexture);
    void SetTextureFrame(SDL_Rect* newFrame);

private:
    std::string texturePath;
    SDL_Texture* texture;
    SDL_Rect* textureFrame;
};

#endif