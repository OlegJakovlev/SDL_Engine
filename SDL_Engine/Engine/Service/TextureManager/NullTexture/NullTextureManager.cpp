#include "NullTextureManager.h"

SDL_Texture* NullTextureManager::GetTexture(const std::string& texturePath) {
    return nullptr;
}

void NullTextureManager::AddTexture(const std::string& texturePath) {
}
