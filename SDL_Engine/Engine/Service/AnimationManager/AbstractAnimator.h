#pragma once

#ifndef AbstractAnimator_H
#define AbstractAnimator_H

#include <unordered_map>
#include <string>
#include <SDL.h>

class AbstractAnimator {
public:
    virtual ~AbstractAnimator();

    virtual void AddAnimation(const std::string& animationName, std::vector<SDL_Texture*> frames) = 0;
    virtual const std::vector<SDL_Texture*>& GetAnimation(const std::string& animationName) const = 0;

protected:
    std::unordered_map<std::string, std::vector<SDL_Texture*>> animations;
};

#endif