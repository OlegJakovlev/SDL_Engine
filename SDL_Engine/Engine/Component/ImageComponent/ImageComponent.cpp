#include "ImageComponent.h"
#include "../../Graphics/Graphics.h"

ImageComponent::~ImageComponent() {
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

void ImageComponent::Init() {
    AbstractComponent::Init();

    SDL_Surface* surface = IMG_Load(pathToImage.c_str());
    if (surface == nullptr) GraphicsLogger::Instance().LogError("Can not access image by path: " + pathToImage);

    if (texture != nullptr) SDL_DestroyTexture(texture);
    texture = Graphics::Instance()->GetTextureFromSurface(surface);
}

void ImageComponent::LoadConfig(const nlohmann::json& config) {
    pathToImage = config.at("imagePath");
}

void ImageComponent::Render() {
    Graphics::Instance()->RenderCopyAdvanced(texture, nullptr, &renderHolder);
}
