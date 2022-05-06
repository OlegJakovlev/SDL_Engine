#pragma once

#ifndef Audio_H
#define Audio_H

#include <string>
#include <unordered_map>
#include <SDL_mixer.h>
#include "../../Logger/AudioLogger/AudioLogger.h"

class Audio {
public:
	virtual ~Audio();
	virtual void PlaySound(const std::string& soundName) = 0;
	virtual void PlayMusic(const std::string& musicName) = 0;

	virtual void PauseSound(const std::string& soundName) = 0;
	virtual void PauseMusic(const std::string& musicName) = 0;

	virtual void ResumeSound(const std::string& soundName) = 0;
	virtual void ResumeMusic(const std::string& musicName) = 0;

	virtual void StopAllSound() = 0;
	virtual void StopAllMusic() = 0;

	void AddMusic(const std::string& musicName, const std::string& path);
	void AddSound(const std::string& soundName, const std::string& path);

protected:
	std::unordered_map<std::string, Mix_Chunk*> sounds;
	std::unordered_map<std::string, Mix_Music*> music;
};

#endif