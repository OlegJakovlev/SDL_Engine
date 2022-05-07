#include "AnimatorLocator.h"

AbstractAnimator* AnimatorLocator::service = nullptr;
NullAnimator AnimatorLocator::nullService = NullAnimator();

// Always returns valid pointer (animator or null service)
AbstractAnimator* AnimatorLocator::GetAnimator() {
	return service;
}

void AnimatorLocator::LinkAnimator(AbstractAnimator* newService) {
	if (newService == nullptr) ReleaseAnimator();
	else service = newService;
}

void AnimatorLocator::ReleaseAnimator() {
	if (service != &nullService) delete service;
	service = &nullService;
}
