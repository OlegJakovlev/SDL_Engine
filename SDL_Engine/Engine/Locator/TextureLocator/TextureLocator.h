#pragma once 

#ifndef TextureLocator_H
#define TextureLocator_H

#include "../../Service/TextureManager/AbstractTextureManager.h"
#include "../../Service/TextureManager/NullTexture/NullTextureManager.h"

class TextureLocator {
public:
	static AbstractTextureManager* GetTextureManager();
	static void LinkTextureManager(AbstractTextureManager* newService);
	static void ReleaseTextureManager();

private:
	static AbstractTextureManager* service;
	static NullTextureManager nullService;
};

#endif