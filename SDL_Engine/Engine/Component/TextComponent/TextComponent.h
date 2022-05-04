#pragma once

#include <string>
#include "../../SDL_Font_Cache/SDL_FontCache.h"
#include "../AbstractComponent.h"

class TextComponent : public AbstractComponent
{
public:
    ~TextComponent();

    void Init() override;
    void LoadConfig(const nlohmann::json& config) override;
    void Render() override;

    void SetText(const std::string& newText);

private:
    FC_Font *font;
    std::string fontPath;
    int fontSize;
    SDL_Color textColor;
    std::string text;
};

