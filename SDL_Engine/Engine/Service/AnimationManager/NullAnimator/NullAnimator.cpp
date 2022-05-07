#include "NullAnimator.h"

void NullAnimator::AddAnimation(const std::string& animationName, std::vector<SDL_Texture*> frames) {
}

// Returns empty vector
const std::vector<SDL_Texture*>& NullAnimator::GetAnimation(const std::string& animationName) const {
    return std::vector<SDL_Texture*>(0);
}
