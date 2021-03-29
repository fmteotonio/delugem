#include "SoundManager.h"

#include <iostream>

const int SoundManager::cAudioFrequency = 66150;
const int SoundManager::cAudioChannelNumber = 2;
const int SoundManager::cAudioChunkSize = 4096;

SoundManager* SoundManager::_soundManagerInstance = nullptr;

SoundManager* SoundManager::Instance() {
	if (!_soundManagerInstance) {
		_soundManagerInstance = new SoundManager();
		Mix_OpenAudio(cAudioFrequency, AUDIO_S16, cAudioChannelNumber, cAudioChunkSize);
	}
	return _soundManagerInstance;
}

void SoundManager::Load(std::string filename, std::string id, SoundManager::soundType type, int volume) {
	if (type == SoundManager::soundType::MUSIC) {
		Mix_Music* pMusic = Mix_LoadMUS(filename.c_str());
		if (pMusic) {
			_musics.insert({ id, pMusic });
			SetMusicVolume(volume);
		}
		else
			std::cerr << "Music could not be loaded: " << SDL_GetError() << std::endl;
	}
	else if (type == SoundManager::soundType::SFX) {
		Mix_Chunk* pSFX = Mix_LoadWAV(filename.c_str());
		if (pSFX) {
			_sfxs.insert({ id, pSFX });
			SetSFXVolume(id, volume);
		}
		else
			std::cerr << "SFX could not be loaded: " << SDL_GetError() << std::endl;
	}
}

void SoundManager::PlayMusic(std::string id, int loop) {
	Mix_PlayMusic(_musics.at(id), loop);
}

void SoundManager::StopMusic() {
	Mix_HaltMusic();
}

void SoundManager::SetMusicVolume(int volume) {
	Mix_VolumeMusic(volume);
}

void SoundManager::PlaySFX(std::string id) {
	Mix_PlayChannel(-1, _sfxs.at(id), false);
}

void SoundManager::SetSFXVolume(std::string id, int volume) {
	Mix_VolumeChunk(_sfxs.at(id), volume);
}

void SoundManager::Clean() {
	Mix_CloseAudio();
	delete _soundManagerInstance;
}