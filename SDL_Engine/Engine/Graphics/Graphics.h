#pragma once

#ifndef Graphics_H
#define Graphics_H

#include <vector>
#include <SDL.h>
#include "../Logger/GraphicsLogger/GraphicsLogger.h"

class Graphics {
public:
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;

    static Graphics* Instance();
    void Clear();
    void Render();

    SDL_Renderer* GetRenderer();
    static void Release();

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
