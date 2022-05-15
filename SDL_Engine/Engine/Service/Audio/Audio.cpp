#include "Audio.h"

Audio::Audio() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) AudioLogger::Instance().LogError("Audio Mixer is not initialized!");

	currentSoundLevel = 128;
	currentMusicLevel = 128;

	soundEffectsStatus = true;
	musicEffectsStatus = true;
}

Audio::~Audio() {
	// Free the sounds
	for (auto& it : sounds) {
		Mix_FreeChunk(it.second);
		it.second = nullptr;
	}

	// Free the music
	for (auto& it : music) {
		Mix_FreeMusic(it.second);
		it.second = nullptr;
	}

	Mix_CloseAudio();
}

void Audio::AddMusic(const std::string& musicName, const std::string& path) {
	Mix_Music* newMusic = Mix_LoadMUS(path.c_str());

	if (newMusic == nullptr) {
		AudioLogger::Instance().LogError('`' + musicName + '`' + " music can not be accessed by following path: " + path);
		return;
	}
	else {
		AudioLogger::Instance().LogMessage('`' + musicName + '`' + " music was loaded succesfully!");
	}

	music.emplace(std::make_pair(musicName, newMusic));
}

void Audio::AddSound(const std::string& soundName, const std::string& path) {
	Mix_Chunk* newSound = Mix_LoadWAV(path.c_str());

	if (newSound == nullptr) {
		AudioLogger::Instance().LogError('`' + soundName + '`' + " sound can not be accessed by following path: " + path);
		return;
	}
	else {
		AudioLogger::Instance().LogMessage('`' + soundName + '`' + " sound was loaded succesfully!");
	}

	sounds.emplace(std::make_pair(soundName, newSound));
}

void Audio::IncreaseSoundVolume() {
	if (currentSoundLevel + 16 > 128) return;
	currentSoundLevel+= 16;

	AudioLogger::Instance().LogMessage("Sound Level was increased: " + std::to_string(currentSoundLevel));
	Mix_Volume(-1, currentSoundLevel);
}

void Audio::IncreaseMusicVolume() {
	if (currentMusicLevel + 16 > 128) return;
	currentMusicLevel += 16;

	AudioLogger::Instance().LogMessage("Music Level was increased: " + std::to_string(currentMusicLevel));
	Mix_VolumeMusic(currentMusicLevel);
}

void Audio::DecreaseSoundVolume() {
	if (currentSoundLevel - 16 < 0) return;
	currentSoundLevel -= 16;

	AudioLogger::Instance().LogMessage("Sound Level was decreased: " + std::to_string(currentSoundLevel));
	Mix_Volume(-1, currentSoundLevel);
}

void Audio::DecreaseMusicVolume() {
	if (currentMusicLevel - 16 < 0) return;
	currentMusicLevel -= 16;

	AudioLogger::Instance().LogMessage("Music Level was decreased: " + std::to_string(currentMusicLevel));
	Mix_VolumeMusic(currentMusicLevel);
}

void Audio::ToggleSoundEffects() {
	soundEffectsStatus = !soundEffectsStatus;

	std::string textStatus = (soundEffectsStatus) ? "ON" : "OFF";
	AudioLogger::Instance().LogMessage("Sound Effects Status: " + textStatus);
}

void Audio::ToggleMusicEffects() {
	musicEffectsStatus = !musicEffectsStatus;
	Mix_VolumeMusic((musicEffectsStatus) ? currentMusicLevel : 0);

	std::string textStatus = (musicEffectsStatus) ? "ON" : "OFF";
	AudioLogger::Instance().LogMessage("Music Effects Status: " + textStatus);
}
