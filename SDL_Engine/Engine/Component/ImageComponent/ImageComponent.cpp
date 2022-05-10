#include "ImageComponent.h"
#include "../../Graphics/Graphics.h"

ImageComponent::~ImageComponent() {
    delete textureFrame;
    texture = nullptr;
}

void ImageComponent::Init() {
    AbstractComponent::Init();

    // Load texture
    SetTexture(TextureLocator::GetTextureManager()->GetTexture(pathToImage.c_str()));
}

void ImageComponent::LoadConfig(const nlohmann::json& config) {
    pathToImage = config.at("imagePath");
}

void ImageComponent::Render() {
    Graphics::Instance()->RenderCopyAdvanced(texture, textureFrame, &renderHolder, objectLinkedTo->GetRotation());
}

SDL_Texture* ImageComponent::GetTexture() const {
    return texture;
}

void ImageComponent::SetTexture(SDL_Texture* newTexture) {
    texture = newTexture;
}

void ImageComponent::SetTextureFrame(SDL_Rect* newFrame) {
    textureFrame = newFrame;
}
