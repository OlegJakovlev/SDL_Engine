#pragma once

#ifndef AnimatorConfigurator_H
#define AnimatorConfigurator_H

#include <regex>
#include "../Configurator.h"
#include "../../Locator/AnimatorLocator/AnimatorLocator.h"
#include "../../Service/AnimationManager/RegularAnimator/RegularAnimator.h"
#include "../../Locator/TextureLocator/TextureLocator.h"

class AnimatorConfigurator : public Configurator {
public:
	explicit AnimatorConfigurator(const std::string& animationsPath);
	~AnimatorConfigurator();

	virtual void LoadConfiguration() override;

private:
	AnimationData::AnimationType GetLoopType(const std::string& loopType);
};

#endif