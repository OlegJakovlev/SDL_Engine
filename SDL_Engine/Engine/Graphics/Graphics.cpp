#include "Graphics.h"

Graphics* Graphics::sInstance = nullptr;

Graphics* Graphics::Instance() {
    if (sInstance == nullptr) sInstance = new Graphics();
    return sInstance;
}

Graphics::Graphics() {
    window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Logger::Instance().LogError("SDL initialization failed!");
        return;
    }

    window = SDL_CreateWindow("4 Bombers - Olegs Jakovlevs (25187386) - CGP2015M Game Programming",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN );

    if (window == nullptr) {
        GraphicsLogger::Instance().LogError("SDL Window ERROR" + std::string(SDL_GetError()));
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    // Ensure the aspect ratio of the original window is sustained
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Make logical resolution as factor of the actual window resolution
    SDL_RenderSetIntegerScale(renderer, SDL_bool::SDL_TRUE);
}

Graphics::~Graphics() {
    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
}

void Graphics::RenderClear() {
    // Clear the current rendering buffer
    SDL_RenderClear(renderer);
}

void Graphics::Render(GameObject::GameObject* gameObject) {
    gameObject->Render();
}

void Graphics::Render(std::vector<GameObject::GameObject*>& sceneObjects, double normalizedStepBetweenUpdates){
    // Layer rendering
    for (int i = 16; i >= 0; i--) {
        std::for_each(sceneObjects.begin(), sceneObjects.end(), [&i](GameObject::GameObject* sceneObject) {
            if (sceneObject->GetLayer() == i) {
                sceneObject->Render();
            }
        });
    }
}

void Graphics::RenderPresent() {
    // Display everything rendered using SDL_RenderCopy, from last SDL_RenderClear call and switch buffer
    SDL_RenderPresent(renderer);
}

SDL_Texture* Graphics::LoadTexture(const std::string& pathToFile) {
    return IMG_LoadTexture(renderer, pathToFile.c_str());
}

SDL_Texture* Graphics::GetTextureFromSurface(SDL_Surface* surface) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    return texture;
}

void Graphics::Release() {
    delete sInstance;
    sInstance = nullptr;
}

SDL_Renderer* Graphics::GetRenderer() {
    return renderer;
}

void Graphics::RenderRectangle(const SDL_Rect* rect) {
    SDL_RenderDrawRect(renderer, rect);
}

void Graphics::RenderCopyAdvanced(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* destRect, const double angle, const SDL_Point* rotationCenter, const SDL_RendererFlip flip) {
    SDL_RenderCopyEx(renderer, texture, srcRect, destRect, angle, rotationCenter, flip);
}