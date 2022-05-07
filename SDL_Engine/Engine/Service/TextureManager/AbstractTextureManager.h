#pragma once

#ifndef AbstractTextureManager_H
#define AbstractTextureManager_H

#include <SDL_image.h>
#include <unordered_map>
#include <string>

class Graphics;

class AbstractTextureManager {
public:
    virtual ~AbstractTextureManager();

    virtual SDL_Texture* GetTexture(const std::string & texturePath) = 0;
    virtual void AddTexture(const std::string & texturePath) = 0;

protected:
    SDL_Texture* LoadTexture(const std::string & pathToFile);
    SDL_Texture* GetTextureFromSurface(SDL_Surface * surface);

    std::unordered_map<std::string, SDL_Texture*> loadedTextures;
};

#endif