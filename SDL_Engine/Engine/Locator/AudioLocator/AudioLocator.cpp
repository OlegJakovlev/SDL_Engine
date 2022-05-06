#include "AudioLocator.h"

Audio* AudioLocator::service = nullptr;
NullAudio AudioLocator::nullService = NullAudio();

Audio* AudioLocator::GetAudio() {
	return service;
}

void AudioLocator::LinkAudio(Audio* newService) {
	if (newService == nullptr) ReleaseAudio();
	else service = newService;
}

void AudioLocator::ReleaseAudio() {
	delete service;
	service = &nullService;
}
