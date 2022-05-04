#include "TextComponent.h"
#include "../../Graphics/Graphics.h"

TextComponent::~TextComponent() {
    FC_FreeFont(font);
    font = nullptr;
}

void TextComponent::Init() {
    AbstractComponent::Init();

    font = FC_CreateFont();
    FC_LoadFont(font, Graphics::Instance()->GetRenderer(), fontPath.c_str(), fontSize, textColor, TTF_STYLE_NORMAL);
}

void TextComponent::LoadConfig(const nlohmann::json& config) {
    nlohmann::json colorConfig = config.at("color");
    textColor = SDL_Color {
        colorConfig.at("r"), colorConfig.at("g"), colorConfig.at("b"), colorConfig.at("a")
    };

    fontSize = config.at("fontSize");
    fontPath = config.at("fontPath");
}

void TextComponent::Render() {
    FC_Draw(font, Graphics::Instance()->GetRenderer(), renderHolder.x, renderHolder.y, text.c_str());
}

void TextComponent::SetText(const std::string& newText) {
    text = newText;
}