#include "ImageComponent.h"
#include "../../Graphics/Graphics.h"

ImageComponent::~ImageComponent() {
    delete textureFrame;
    texture = nullptr;
}

void ImageComponent::Init() {
    AbstractComponent::Init();

    SetTexture(TextureLocator::GetTextureManager()->GetTexture(texturePath));
}

void ImageComponent::LoadConfig(const nlohmann::json& config) {
    texturePath = config.value("imagePath", "");
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
