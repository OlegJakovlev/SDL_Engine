#include "AbstractAnimator.h"

AbstractAnimator::~AbstractAnimator() {
    for (auto& it : animations) {
        it.second.clear();
    }

    animations.clear();
}
