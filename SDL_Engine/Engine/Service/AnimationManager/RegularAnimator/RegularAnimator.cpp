#include "RegularAnimator.h"

void RegularAnimator::AddAnimation(const std::string& animationName, std::vector<SDL_Texture*> frames) {
    animations.emplace(std::make_pair(animationName, frames));
}

const std::vector<SDL_Texture*>& RegularAnimator::GetAnimation(const std::string& animationName) const {
    if (animations.find(animationName) == animations.end()) return std::vector<SDL_Texture*>(0);
    return animations.at(animationName);
}
