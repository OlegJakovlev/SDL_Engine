#include "TextureLocator.h"

AbstractTextureManager* TextureLocator::service = nullptr;
NullTextureManager TextureLocator::nullService = NullTextureManager();

// Always returns valid pointer (or null service)
AbstractTextureManager* TextureLocator::GetTextureManager() {
	return service;
}

void TextureLocator::LinkTextureManager(AbstractTextureManager* newService) {
	if (newService == nullptr) ReleaseTextureManager();
	else service = newService;
}

void TextureLocator::ReleaseTextureManager() {
	if (service != &nullService) delete service;
	service = &nullService;
}
