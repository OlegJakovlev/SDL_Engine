#pragma once

#ifndef RegularAnimator_H
#define RegularAnimator_H

#include "../AbstractAnimator.h"
#include "../../../Logger/GraphicsLogger/GraphicsLogger.h"

class RegularAnimator : public AbstractAnimator {
public:
    virtual void AddAnimation(const std::string& animationName, std::vector<SDL_Texture*> frames) override;
    virtual const std::vector<SDL_Texture*>& GetAnimation(const std::string& animationName) const override;
};

#endif