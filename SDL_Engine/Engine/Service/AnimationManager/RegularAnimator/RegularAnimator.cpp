#include "RegularAnimator.h"

void RegularAnimator::AddAnimation(const std::string& animationName, AnimationData& animation) {
    animations.emplace(std::make_pair(animationName, animation));
}

const AnimationData& RegularAnimator::GetAnimation(const std::string& animationName) const {
    if (animations.find(animationName) == animations.end()) return AnimationData();
    return animations.at(animationName);
}
