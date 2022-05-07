#include "TextureManager.h"

SDL_Texture* TextureManager::GetTexture(const std::string& texturePath) {
    if (loadedTextures.find(texturePath) == loadedTextures.end()) return nullptr;
    return loadedTextures.at(texturePath);
}

void TextureManager::AddTexture(const std::string& texturePath) {
    SDL_Texture* newTexture = LoadTexture(texturePath);

    if (newTexture == nullptr) {
        GraphicsLogger::Instance().LogError("Following texture can not be loaded: " + texturePath);
        return;
    }
    else {
        GraphicsLogger::Instance().LogMessage("Texture by following path was loaded: " + texturePath);
    }

    loadedTextures.emplace(texturePath, newTexture);
}