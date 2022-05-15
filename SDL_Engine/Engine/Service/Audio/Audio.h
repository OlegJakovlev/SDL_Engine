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
	virtual void PauseMusic() = 0;

	virtual void ResumeSound(const std::string& soundName) = 0;
	virtual void ResumeMusic() = 0;

	virtual void StopAllSound() = 0;
	virtual void StopAllMusic() = 0;

	virtual void AddMusic(const std::string& musicName, const std::string& path);
	virtual void AddSound(const std::string& soundName, const std::string& path);

	virtual void IncreaseSoundVolume();
	virtual void IncreaseMusicVolume();

	virtual void DecreaseSoundVolume();
	virtual void DecreaseMusicVolume();

	virtual void ToggleSoundEffects();
	virtual void ToggleMusicEffects();

protected:
	Audio();

	int currentSoundLevel;
	int currentMusicLevel;

	bool soundEffectsStatus;
	bool musicEffectsStatus;

	std::unordered_map<std::string, Mix_Chunk*> sounds;
	std::unordered_map<std::string, Mix_Music*> music;

	std::unordered_map<Mix_Chunk*, int> activeSoundChannel;
	std::unordered_map<Mix_Music*, int> activeMusicChannel;
};

#endif