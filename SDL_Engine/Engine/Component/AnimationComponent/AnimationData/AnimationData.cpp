#include "AnimationData.h"

AnimationData::~AnimationData() {
    fullTexture = nullptr;
    animationFrames.clear();
    frameDelays.clear();
}
