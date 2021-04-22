#include "SoundManager.h"

#include <iostream>

const Sound SoundManager::cGameMusic      ={ "Game" ,     "res/sounds/game.ogg",      Sound::Type::MUSIC, 16 };
const Sound SoundManager::cBreakSound     ={ "Break" ,    "res/sounds/break.wav",     Sound::Type::SFX,   16 };
const Sound SoundManager::cFillSound      ={ "Fill" ,     "res/sounds/fill.wav",      Sound::Type::SFX,   24 };
const Sound SoundManager::cLevelUpSound   ={ "LevelUp" ,  "res/sounds/levelup.wav",   Sound::Type::SFX,   20 };
const Sound SoundManager::cLoseSound      ={ "Lose" ,     "res/sounds/lose.wav",      Sound::Type::SFX,   32 };
const Sound SoundManager::cPushSound      ={ "Push" ,     "res/sounds/push.wav",      Sound::Type::SFX,   16 };
const Sound SoundManager::cSelectSound    ={ "Select" ,   "res/sounds/select.wav",    Sound::Type::SFX,   16 };
const Sound SoundManager::cStartSound     ={ "Start" ,    "res/sounds/start.wav",     Sound::Type::SFX,   24 };
const Sound SoundManager::cTitleFallSound ={ "TitleFall", "res/sounds/titlefall.wav", Sound::Type::SFX,   28 };

const int SoundManager::cAudioFrequency     = 66150;
const int SoundManager::cAudioChannelNumber = 2;
const int SoundManager::cAudioChunkSize     = 4096;

SoundManager* SoundManager::_soundManagerInstance = nullptr;

SoundManager* SoundManager::Instance() {
	if (!_soundManagerInstance) {
		_soundManagerInstance = new SoundManager();
		Mix_OpenAudio(cAudioFrequency, AUDIO_S16, cAudioChannelNumber, cAudioChunkSize);
	}
	return _soundManagerInstance;
}

void SoundManager::Load(Sound sound) {
	if (sound.type == Sound::Type::MUSIC) {
		Mix_Music* pMusic = Mix_LoadMUS(sound.path.c_str());
		if (pMusic)
			_musics.insert({ sound.id, pMusic });
		else
			std::cerr << "Music could not be loaded: " << SDL_GetError() << std::endl;
	}
	else if (sound.type == Sound::Type::SFX) {
		Mix_Chunk* pSFX = Mix_LoadWAV(sound.path.c_str());
		if (pSFX) {
			_sfxs.insert({ sound.id, pSFX });
			SetSFXVolume(sound.id, sound.volume);
		}
		else
			std::cerr << "SFX could not be loaded: " << SDL_GetError() << std::endl;
	}
}

void SoundManager::LoadAllSound() {
	//Load Music
	Load(cGameMusic);

	//Load SFX
	Load(cBreakSound);
	Load(cFillSound);
	Load(cLevelUpSound);
	Load(cLoseSound);
	Load(cPushSound);
	Load(cSelectSound);
	Load(cStartSound);
	Load(cTitleFallSound);
}

void SoundManager::PlayMusic(Sound music, int loops) {
	Mix_PlayMusic(_musics.at(music.id), loops);
	SetMusicVolume(music.volume);
}

void SoundManager::StopMusic() {
	Mix_HaltMusic();
}

void SoundManager::SetMusicVolume(int volume) {
	Mix_VolumeMusic(volume);
}

void SoundManager::PlaySFX(Sound sfx) {
	Mix_PlayChannel(-1, _sfxs.at(sfx.id), false);
}

void SoundManager::SetSFXVolume(std::string id, int volume) {
	Mix_VolumeChunk(_sfxs.at(id), volume);
}

void SoundManager::Clean() {
	Mix_CloseAudio();
	delete _soundManagerInstance;
}