#pragma once

#ifndef AnimationComponent_H
#define AnimationComponent_H

#include <SDL_image.h>
#include "../AbstractComponent.h"
#include "../../Locator/AnimatorLocator/AnimatorLocator.h"
#include "../ImageComponent/ImageComponent.h"
#include "../../Timer/Timer.h"

class AnimationComponent : public AbstractComponent {
public:
    ~AnimationComponent();

    void Init() override;
    void Update() override;

    void PlayAnimation(const std::string& animationName);
    void PauseAnimation();
    void HaltAnimation();

private:
    AnimationData animationData;
    int currentFrameIndex;
    int step;

    ImageComponent* imageComponent;
    SDL_Texture* beforeAnimationTexture;

    Timer timer;
    double previosFrameTime;

    bool isPaused = false;
    bool isFinished;
};

#endif