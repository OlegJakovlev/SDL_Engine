#include "AnimatorConfigurator.h"

AnimatorConfigurator::AnimatorConfigurator(const std::string& animationsConfigPath) : Configurator(animationsConfigPath) {
}

AnimatorConfigurator::~AnimatorConfigurator() {
	AnimatorLocator::ReleaseAnimator();
}

void AnimatorConfigurator::LoadConfiguration() {
	Configurator::LoadConfiguration();

	AbstractAnimator* animatorService = new RegularAnimator();
	AnimatorLocator::LinkAnimator(animatorService);

	AbstractTextureManager* textureManager = TextureLocator::GetTextureManager();

	for (auto& animationEntry : configuration.items()) {
		AnimationData newAnimation;

		nlohmann::json animationData = configuration.at(animationEntry.key());

		newAnimation.fullTexture = textureManager->GetTexture(animationData.at("animationSheet"));
		newAnimation.frameDelays = animationData.at("frameDelays").get<std::vector<float>>();
		newAnimation.loop = GetLoopType(animationData.at("loop").get<std::string>());

		// Create frames
		for (int frameIndex = 0; frameIndex < newAnimation.frameDelays.size(); frameIndex++) {
			SDL_Rect animationFrame{32 * frameIndex, 0, 32, 32};
			newAnimation.animationFrames.push_back(animationFrame);
		}

		// Add new animation
		animatorService->AddAnimation(animationEntry.key(), newAnimation);
	}
}

AnimationData::AnimationType AnimatorConfigurator::GetLoopType(const std::string& loopType) {
	if (loopType == "ONE_OFF") return AnimationData::AnimationType::ONE_OFF;
	else if (loopType == "LOOP") return AnimationData::AnimationType::LOOP;
	else if (loopType == "PING_PONG") return AnimationData::AnimationType::PING_PONG;
}
