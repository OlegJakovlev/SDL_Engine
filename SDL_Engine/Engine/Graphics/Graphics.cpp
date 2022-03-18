#include "Graphics.h"

Graphics* Graphics::sInstance = nullptr;

Graphics* Graphics::Instance() {
    if (sInstance == nullptr) sInstance = new Graphics();
    return sInstance;
}

void Graphics::Clear() {
    // Clear the current rendering buffer
    SDL_RenderClear(renderer);
}

Graphics::Graphics() {
    window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Logger::Instance().LogError("SDL initialization failed!");
        return;
    }

    window = SDL_CreateWindow("4 Bombers - Olegs Jakovlevs (25187386) - CGP2015M Game Programming", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        GraphicsLogger::Instance().LogError("SDL Window ERROR" + std::string(SDL_GetError()));
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Renderer* Graphics::GetRenderer() {
    return renderer;
}

Graphics::~Graphics() {
    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
}

void Graphics::Render() {
    // Display everything rendered using SDL_RenderCopy, from last SDL_RenderClear call and switch buffer
    SDL_RenderPresent(renderer);
}

void Graphics::Release() {
    delete sInstance;
    sInstance = nullptr;
}
