#pragma once

#ifndef RegularAnimator_H
#define RegularAnimator_H

#include "../AbstractAnimator.h"
#include "../../../Logger/GraphicsLogger/GraphicsLogger.h"

class RegularAnimator : public AbstractAnimator {
public:
    void AddAnimation(const std::string& animationName, AnimationData& animation) override;
    const AnimationData& GetAnimation(const std::string& animationName) const override;
};

#endif