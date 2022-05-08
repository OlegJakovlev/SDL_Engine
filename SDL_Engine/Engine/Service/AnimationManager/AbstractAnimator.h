#pragma once

#ifndef AbstractAnimator_H
#define AbstractAnimator_H

#include <unordered_map>
#include <string>
#include "../../AnimationData/AnimationData.h"

class AbstractAnimator {
public:
    virtual ~AbstractAnimator();

    virtual void AddAnimation(const std::string& animationName, AnimationData& animation) = 0;
    virtual const AnimationData& GetAnimation(const std::string& animationName) const = 0;

protected:
    std::unordered_map<std::string, AnimationData> animations;
};

#endif