#include "AbstractAnimator.h"

AbstractAnimator::~AbstractAnimator() {
    for (auto it : animations) {
        delete &it.second;
    }

    animations.clear();
}
