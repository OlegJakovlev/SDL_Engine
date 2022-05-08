#include "AnimatorConfigurator.h"

AnimatorConfigurator::AnimatorConfigurator(const std::string& configPath) : Configurator(configPath) {
}

AnimatorConfigurator::~AnimatorConfigurator() {
	AnimatorLocator::ReleaseAnimator();
}

void AnimatorConfigurator::LoadConfiguration() {
	Configurator::LoadConfiguration();

	AbstractAnimator* animatorService = new RegularAnimator();
	AnimatorLocator::LinkAnimator(animatorService);


}
