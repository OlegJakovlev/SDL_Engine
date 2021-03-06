#pragma once

#ifndef PCAudio_H
#define PCAudio_H

#include "../Audio.h"

class PCAudio : public Audio {
public:
	PCAudio();

	virtual void PlaySound(const std::string& soundName) override;
	virtual void PlayMusic(const std::string& musicName) override;

	virtual void PauseSound(const std::string& soundName) override;
	virtual void PauseMusic() override;

	virtual void ResumeSound(const std::string& soundName) override;
	virtual void ResumeMusic() override;

	virtual void StopAllSound() override;
	virtual void StopAllMusic() override;

	virtual void IncreaseSoundVolume() override;
	virtual void IncreaseMusicVolume() override;

	virtual void DecreaseSoundVolume() override;
	virtual void DecreaseMusicVolume() override;

	virtual void ToggleSoundEffects() override;
	virtual void ToggleMusicEffects() override;
};

#endif