#pragma once

#ifndef AnimationData_H
#define AnimationData_H

#include <vector>
#include <SDL_image.h>

struct AnimationData {
    AnimationData() = default;
    ~AnimationData();

    enum class AnimationType {
        ONE_OFF,
        LOOP,
        PING_PONG
    };

    SDL_Texture* fullTexture;
    std::vector<SDL_Rect> animationFrames;
    std::vector<float> frameDelays;
    AnimationType loop;
};

#endif