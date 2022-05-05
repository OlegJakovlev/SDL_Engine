#include "ImageComponent.h"
#include "../../Graphics/Graphics.h"

ImageComponent::~ImageComponent() {
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

void ImageComponent::Init() {
    AbstractComponent::Init();

    // Destroy existing texture
    if (texture != nullptr) SDL_DestroyTexture(texture);

    // Load new texture
    texture = Graphics::Instance()->LoadTexture(pathToImage.c_str());
    if (texture == nullptr) GraphicsLogger::Instance().LogError("Can not access image by path: " + pathToImage);
}

void ImageComponent::LoadConfig(const nlohmann::json& config) {
    pathToImage = config.at("imagePath");
}

void ImageComponent::Render() {
    Graphics::Instance()->RenderCopyAdvanced(texture, nullptr, &renderHolder, objectLinkedTo->GetRotation());
}
