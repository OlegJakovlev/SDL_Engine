#include "AudioConfigurator.h"

AudioConfigurator::AudioConfigurator(const std::string& configPath) : Configurator(configPath) {
}

AudioConfigurator::~AudioConfigurator() {
	AudioLocator::ReleaseAudio();
}

void AudioConfigurator::LoadConfiguration() {
	Configurator::LoadConfiguration();

	Audio* audioService = new PCAudio();
	AudioLocator::LinkAudio(audioService);

	for (auto& soundEntry : configuration.at("sounds")) {
		//std::printf("%s\n", soundEntry);
	}

	for (auto& musicEntry : configuration.at("music")) {
		//std::printf("%s\n", musicEntry);
	}
}
