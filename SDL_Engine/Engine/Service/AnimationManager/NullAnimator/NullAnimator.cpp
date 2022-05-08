#include "NullAnimator.h"

void NullAnimator::AddAnimation(const std::string& animationName, AnimationData& animation) {
}

// Returns empty animation
const AnimationData& NullAnimator::GetAnimation(const std::string& animationName) const {
    return AnimationData();
}
