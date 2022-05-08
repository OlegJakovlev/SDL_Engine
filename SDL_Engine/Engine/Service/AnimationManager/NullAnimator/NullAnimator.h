#pragma once

#ifndef NullAnimator_H
#define NullAnimator_H

#include "../AbstractAnimator.h"

class NullAnimator : public AbstractAnimator {
public:
	NullAnimator() = default;

	void AddAnimation(const std::string& animationName, AnimationData& animation) override;
	const AnimationData& GetAnimation(const std::string& animationName) const override;
};

#endif