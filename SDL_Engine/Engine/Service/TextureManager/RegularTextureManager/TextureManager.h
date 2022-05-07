#pragma once

#ifndef TextureManager_H
#define TextureManager_H

#include "../AbstractTextureManager.h"
#include "../../../Logger/GraphicsLogger/GraphicsLogger.h"

class TextureManager : public AbstractTextureManager {
public:
    TextureManager() = default;
    ~TextureManager() = default;

    SDL_Texture* GetTexture(const std::string& texturePath) override;
    void AddTexture(const std::string& texturePath) override;
};

#endif