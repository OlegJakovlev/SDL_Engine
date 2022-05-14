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

	if (configuration.empty()) return;

	for (auto& soundEntry : configuration.at("sounds").items()) {
		audioService->AddSound(soundEntry.key(), soundEntry.value());
	}

	for (auto& musicEntry : configuration.at("music").items()) {
		audioService->AddMusic(musicEntry.key(), musicEntry.value());
	}
}
