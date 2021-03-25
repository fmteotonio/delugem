#include "SoundManager.h"

#include <iostream>

SoundManager* SoundManager::sSoundManagerInstance_ = nullptr;

SoundManager::SoundManager() {
	Mix_OpenAudio(66150, AUDIO_S16, 2, 4096);
}

SoundManager* SoundManager::Instance() {
	if (!sSoundManagerInstance_) {
		sSoundManagerInstance_ = new SoundManager();
	}
	return sSoundManagerInstance_;
}

bool SoundManager::Load(std::string filename, std::string id, SoundManager::soundType type, int volume) {
	if (type == SoundManager::soundType::MUSIC) {
		Mix_Music* pMusic = Mix_LoadMUS(filename.c_str());
		if (pMusic == 0) {
			std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}
		musics_.insert({ id, pMusic });
		setMusicVolume(volume);
		return true;
	}
	else if (type == SoundManager::soundType::SFX) {
		Mix_Chunk* pSFX = Mix_LoadWAV(filename.c_str());
		if (pSFX == 0) {
			std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}
		sfxs_.insert({ id, pSFX });
		setSFXVolume(id,volume);
		return true;
	}
	return false;
}

void SoundManager::playMusic(std::string id, int loop) {
	Mix_PlayMusic(musics_.at(id), loop);
}
void SoundManager::setMusicPosition(double position) {
	Mix_SetMusicPosition(position);
}

void SoundManager::setMusicVolume(int volume) {
	Mix_VolumeMusic(volume);
}


void SoundManager::playSFX(std::string id, int loop) {
	Mix_PlayChannel(-1, sfxs_.at(id), loop);
}
void SoundManager::setSFXVolume(std::string id, int volume) {
	Mix_VolumeChunk(sfxs_.at(id), volume);
}

void SoundManager::Clean() {
	Mix_CloseAudio();
}