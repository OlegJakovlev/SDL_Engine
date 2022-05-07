#include "AbstractTextureManager.h"
#include "../../Graphics/Graphics.h"

AbstractTextureManager::~AbstractTextureManager() {
    for (auto& textureEntry : loadedTextures) {
        SDL_DestroyTexture(textureEntry.second);
        textureEntry.second = nullptr;
    }

    loadedTextures.clear();
}

SDL_Texture* AbstractTextureManager::LoadTexture(const std::string& pathToFile) {
    return IMG_LoadTexture(Graphics::Instance()->GetRenderer(), pathToFile.c_str());
}

SDL_Texture* AbstractTextureManager::GetTextureFromSurface(SDL_Surface* surface) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Graphics::Instance()->GetRenderer(), surface);
    SDL_FreeSurface(surface);

    return texture;
}
