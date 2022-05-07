#pragma once

#ifndef NullAnimator_H
#define NullAnimator_H

#include "../AbstractAnimator.h"

class NullAnimator : public AbstractAnimator {
public:
	NullAnimator() = default;

	virtual void AddAnimation(const std::string& animationName, std::vector<SDL_Texture*> frames) override;
	virtual const std::vector<SDL_Texture*>& GetAnimation(const std::string& animationName) const override;
};

#endif