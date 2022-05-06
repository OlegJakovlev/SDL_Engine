#pragma once

#ifndef PCAudio_H
#define PCAudio_H

#include "../Audio.h"

class PCAudio : public Audio {
public:
	PCAudio() = default;

	virtual void PlaySound(const std::string& soundName) override;
	virtual void PlayMusic(const std::string& musicName) override;

	virtual void PauseSound(const std::string& soundName) override;
	virtual void PauseMusic(const std::string& musicName) override;

	virtual void ResumeSound(const std::string& soundName) override;
	virtual void ResumeMusic(const std::string& musicName) override;

	virtual void StopAllSound() override;
	virtual void StopAllMusic() override;
};

#endif