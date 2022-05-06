#include "NullAudio.h"

NullAudio::NullAudio() : Audio::Audio() {
}

void NullAudio::PlaySound(const std::string& soundName) {
}

void NullAudio::PlayMusic(const std::string& musicName) {
}

void NullAudio::PauseSound(const std::string& soundName) {
}

void NullAudio::PauseMusic() {
}

void NullAudio::ResumeSound(const std::string& soundName) {
}

void NullAudio::ResumeMusic() {
}

void NullAudio::StopAllSound() {
}

void NullAudio::StopAllMusic() {
}
