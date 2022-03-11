#pragma once

#ifndef Graphics_H
#define Graphics_H

#include <SDL.h>
#include "../Logger/Logger.h"

class Graphics {
public:
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;

    static Graphics* Instance();
    void Render();
    static void Release();

private:
    Graphics();
    Graphics& operator=(const Graphics&) = delete;
    Graphics(const Graphics&) = delete;
    ~Graphics();

    static Graphics* sInstance;

    SDL_Window* window;
    SDL_Surface* backBuffer;
};

#endif
