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

    void RenderClear();
    void Render(GameObject::GameObject* gameObject);
    void Render(std::vector<GameObject::GameObject*>& gameObjects, double normalizedStepBetweenUpdates);
    void RenderPresent();

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
