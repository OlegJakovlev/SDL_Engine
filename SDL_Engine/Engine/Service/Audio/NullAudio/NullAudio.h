#pragma once

#ifndef NullAudio_H
#define NullAudio_H

#include "../Audio.h"

class NullAudio : public Audio {
public:
	NullAudio();

	void PlaySound(const std::string& soundName) override;
	void PlayMusic(const std::string& musicName) override;

	void PauseSound(const std::string& soundName) override;
	void PauseMusic() override;

	void ResumeSound(const std::string& soundName) override;
	void ResumeMusic() override;

	void StopAllSound() override;
	void StopAllMusic() override;
};

#endif