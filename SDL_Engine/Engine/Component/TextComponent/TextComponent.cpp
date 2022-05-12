#include "TextComponent.h"
#include "../../Graphics/Graphics.h"

TextComponent::~TextComponent() {
    FC_FreeFont(font);
    delete font;
    font = nullptr;
}

void TextComponent::Init() {
    AbstractComponent::Init();

    font = FC_CreateFont();
    if (FC_LoadFont(font, Graphics::Instance()->GetRenderer(), fontPath.c_str(), fontSize, textColor, TTF_STYLE_NORMAL) == 0) {
        GraphicsLogger::Instance().LogError("Can not display text! Please check if path provided is correct.");
    }
}

void TextComponent::LoadConfig(const nlohmann::json& config) {
    nlohmann::json colorConfig;

    if (config.contains("color")) {
        colorConfig = config.at("color");
    }
    else {
        colorConfig["r"] = 255;
        colorConfig["g"] = 255;
        colorConfig["b"] = 255;
        colorConfig["a"] = 255;
    }

    textColor = SDL_Color {
        colorConfig.at("r"),
        colorConfig.at("g"),
        colorConfig.at("b"),
        colorConfig.at("a")
    };

    fontSize = config.value("fontSize", 16);
    fontPath = config.value("fontPath", "Resources/Fonts/sans.ttf");
}

void TextComponent::Render() {
    FC_Draw(font, Graphics::Instance()->GetRenderer(), renderHolder.x, renderHolder.y, text.c_str());
}

void TextComponent::SetText(const std::string& newText) {
    text = newText;
}