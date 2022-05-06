#include "PCAudio.h"

PCAudio::PCAudio() : Audio::Audio() {
}

void PCAudio::PlaySound(const std::string& soundName) {
    if (!soundEffectsStatus) return;
    if (sounds.find(soundName) == sounds.end()) return;

    Mix_Chunk* sound = sounds.at(soundName);
    int activeChannel = Mix_PlayChannel(-1, sound, 0);

    activeSoundChannel.emplace(sound, activeChannel);
}

void PCAudio::PlayMusic(const std::string& musicName) {
    if (!musicEffectsStatus) return;
    if (music.find(musicName) == music.end()) return;

    Mix_Music* musicEntry = music.at(musicName);
    int activeChannel = Mix_PlayMusic(musicEntry, 0);

    activeMusicChannel.emplace(musicEntry, activeChannel);
}

void PCAudio::PauseSound(const std::string& soundName) {
    Mix_Pause(activeSoundChannel.at(sounds.at(soundName)));
}

void PCAudio::PauseMusic() {
    Mix_PauseMusic();
}

void PCAudio::ResumeSound(const std::string& soundName) {
    Mix_Resume(activeSoundChannel.at(sounds.at(soundName)));
}

void PCAudio::ResumeMusic() {
    Mix_ResumeMusic();
}

void PCAudio::StopAllSound() {
    Mix_HaltChannel(-1);
}

void PCAudio::StopAllMusic() {
    Mix_HaltMusic();
}