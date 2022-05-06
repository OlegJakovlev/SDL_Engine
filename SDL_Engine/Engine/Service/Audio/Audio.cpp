#include "Audio.h"

Audio::~Audio() {
}

void Audio::AddMusic(const std::string& musicName, const std::string& path) {
	Mix_Music* newMusic = Mix_LoadMUS(path.c_str());

	if (newMusic == nullptr) {
		AudioLogger::Instance().LogError(musicName + " can not be accessed by following path: " + path);
		return;
	}

	music.emplace(std::make_pair(musicName, newMusic));
}

void Audio::AddSound(const std::string& soundName, const std::string& path) {
	Mix_Chunk* newSound = Mix_LoadWAV(path.c_str());

	if (newSound == nullptr) {
		AudioLogger::Instance().LogError(soundName + " can not be accessed by following path: " + path);
		return;
	}

	sounds.emplace(std::make_pair(soundName, newSound));
}
