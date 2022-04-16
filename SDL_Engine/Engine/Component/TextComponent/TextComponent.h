#pragma once

#include <SDL_ttf.h>
#include <string>
#include "../IComponent.h"

class TextComponent : public IComponent
{
public:
    void SetText(std::string newText);

private:
    TTF_Font* font;
    SDL_Color textColor;
    std::string text;
};

