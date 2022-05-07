#pragma once

#ifndef NullTextureManager_H
#define NullTextureManager_H

#include "../AbstractTextureManager.h"

class NullTextureManager : public AbstractTextureManager {
public:
    NullTextureManager() = default;
    ~NullTextureManager() = default;

    SDL_Texture* GetTexture(const std::string& texturePath) override;
    void AddTexture(const std::string& texturePath) override;
};

#endif