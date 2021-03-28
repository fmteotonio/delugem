#include "SoundManager.h"

#include <iostream>

SoundManager* SoundManager::sSoundManagerInstance = nullptr;

SoundManager* SoundManager::Instance() {
	if (!sSoundManagerInstance) {
		sSoundManagerInstance = new SoundManager();
		Mix_OpenAudio(66150, AUDIO_S16, 2, 4096);
	}
	return sSoundManagerInstance;
}

bool SoundManager::Load(std::string filename, std::string id, SoundManager::soundType type, int volume) {
	if (type == SoundManager::soundType::MUSIC) {
		Mix_Music* pMusic = Mix_LoadMUS(filename.c_str());
		if (!pMusic) {
			std::cerr << "Music could not be loaded: " << SDL_GetError() << std::endl;
			return false;
		}
		_musics.insert({ id, pMusic });
		SetMusicVolume(volume);
		return true;
	}
	else if (type == SoundManager::soundType::SFX) {
		Mix_Chunk* pSFX = Mix_LoadWAV(filename.c_str());
		if (!pSFX) {
			std::cerr << "SFX could not be loaded: " << SDL_GetError() << std::endl;
			return false;
		}
		_sfxs.insert({ id, pSFX });
		SetSFXVolume(id,volume);
		return true;
	}
	return false;
}

void SoundManager::PlayMusic(std::string id, int loop) {
	Mix_PlayMusic(_musics.at(id), loop);
}
void SoundManager::StopMusic() {
	Mix_HaltMusic();
}

void SoundManager::SetMusicPosition(double position) {
	Mix_SetMusicPosition(position);
}
void SoundManager::SetMusicVolume(int volume) {
	Mix_VolumeMusic(volume);
}
void SoundManager::PlaySFX(std::string id, int loop) {
	Mix_PlayChannel(-1, _sfxs.at(id), loop);
}
void SoundManager::SetSFXVolume(std::string id, int volume) {
	Mix_VolumeChunk(_sfxs.at(id), volume);
}
void SoundManager::Clean() {
	Mix_CloseAudio();
}