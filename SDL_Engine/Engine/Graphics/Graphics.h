#pragma once

#ifndef Graphics_H
#define Graphics_H

#include <SDL.h>
#include <vector>
#include "../GameObject/GameObject.h"
#include "../Logger/GraphicsLogger/GraphicsLogger.h"

class Graphics {
public:
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;

    static Graphics* Instance();
    static void Release();

    SDL_Renderer* GetRenderer();

    void RenderRectangle(const SDL_Rect* rect);

    void RenderCopyAdvanced(
        SDL_Texture* texture = nullptr,
        const SDL_Rect* srcRect = nullptr,
        const SDL_Rect* destRect = nullptr,
        const double angle = 0,
        const SDL_Point* rotationCenter = nullptr,
        const SDL_RendererFlip flip = SDL_FLIP_NONE
    );

    void RenderClear();
    void Render(GameObject::GameObject* gameObject);
    void Render(std::vector<GameObject::GameObject*>& gameObjects, double normalizedStepBetweenUpdates);
    void RenderPresent();

    SDL_Texture* LoadTexture(const std::string& pathToFile);
    SDL_Texture* GetTextureFromSurface(SDL_Surface* surface);

private:
    Graphics();
    Graphics& operator=(const Graphics&) = delete;
    Graphics(const Graphics&) = delete;
    ~Graphics();

    static Graphics* sInstance;

    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif
