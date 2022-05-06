#pragma once 

#ifndef AudioLocator_H
#define AudioLocator_H

#include "../../Service/Audio/Audio.h"
#include "../../Service/Audio/NullAudio/NullAudio.h"

class AudioLocator {
public:
	static Audio* GetAudio();
	static void LinkAudio(Audio* newService);
	static void ReleaseAudio();

private:
	static Audio* service;
	static NullAudio nullService;
};

#endif