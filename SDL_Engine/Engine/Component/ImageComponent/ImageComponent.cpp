#include "ImageComponent.h"
#include "../../Graphics/Graphics.h"

ImageComponent::~ImageComponent() {
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
    Graphics::Instance()->RenderCopyAdvanced(texture, nullptr, &renderHolder, objectLinkedTo->GetRotation());
}

void ImageComponent::SetTexture(SDL_Texture* newTexture) {
    texture = newTexture;
}
