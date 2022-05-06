#include "AudioLocator.h"

Audio* AudioLocator::service = nullptr;
NullAudio AudioLocator::nullService = NullAudio();

// Always returns valid pointer (audio or null service)
Audio* AudioLocator::GetAudio() {
	return service;
}

void AudioLocator::LinkAudio(Audio* newService) {
	if (newService == nullptr) ReleaseAudio();
	else service = newService;
}

void AudioLocator::ReleaseAudio() {
	if (service != &nullService) delete service;
	service = &nullService;
}
