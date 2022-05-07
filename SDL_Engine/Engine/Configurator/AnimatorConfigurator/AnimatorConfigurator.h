#pragma once

#ifndef AnimatorConfigurator_H
#define AnimatorConfigurator_H

#include "../Configurator.h"
#include "../../Locator/AnimatorLocator/AnimatorLocator.h"
#include "../../Service/AnimationManager/RegularAnimator/RegularAnimator.h"

class AnimatorConfigurator : public Configurator {
public:
	explicit AnimatorConfigurator(const std::string& configPath);
	~AnimatorConfigurator();

	virtual void LoadConfiguration() override;
};

#endif