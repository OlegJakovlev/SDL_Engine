#include "Graphics.h"

Graphics* Graphics::sInstance = nullptr;

Graphics* Graphics::Instance() {
    if (sInstance == nullptr) sInstance = new Graphics();
    return sInstance;
}

Graphics::Graphics() {
    window = nullptr;
    backBuffer = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Logger::Instance().LogError("SDL initialization failed!");
        return;
    }

    window = SDL_CreateWindow("Application", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        Logger::Instance().LogError("SDL Window ERROR" + std::string(SDL_GetError()));
        return;
    }

    backBuffer = SDL_GetWindowSurface(window);
}

Graphics::~Graphics() {
    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
}

void Graphics::Render() {
    SDL_UpdateWindowSurface(window);
}

void Graphics::Release() {
    delete sInstance;
    sInstance = nullptr;
}
