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
    void LoadConfig(const nlohmann::json& config) override;
    void Update() override;

    void PlayAnimation(const std::string& animationName);
    void PauseAnimation();

private:
    std::vector<SDL_Texture*>::const_iterator currentFrame;
    ImageComponent* imageComponent;

    Timer timer;

    double frameSwitchTime;
    double previosFrameTime;

    bool isPlaying = false;
};

#endif