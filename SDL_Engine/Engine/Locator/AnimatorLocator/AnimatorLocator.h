#pragma once 

#ifndef AnimatorLocator_H
#define AnimatorLocator_H

#include "../../Service/AnimationManager/AbstractAnimator.h"
#include "../../Service/AnimationManager/NullAnimator/NullAnimator.h"

class AnimatorLocator {
public:
	static AbstractAnimator* GetAnimator();
	static void LinkAnimator(AbstractAnimator* newService);
	static void ReleaseAnimator();

private:
	static AbstractAnimator* service;
	static NullAnimator nullService;
};

#endif