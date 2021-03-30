#pragma once

#include <map> 
#include <string>

#include <SDL_mixer.h>

#include "structs/Sound.h"

class SoundManager {
public:

	static const Sound cGameMusic;
	static const Sound cBreakSound;
	static const Sound cPushSound;
	static const Sound cFillSound;
	static const Sound cLoseSound;
	static const Sound cStartSound;
	static const Sound cLevelUpSound;
	static const Sound cSelectSound;
	static const Sound cTitleFallSound;

	static const int cAudioFrequency;
	static const int cAudioChannelNumber;
	static const int cAudioChunkSize;

	static SoundManager* Instance();

	void Load(Sound sound);
	void PlayMusic(Sound music, int loops);
	void StopMusic();
	void SetMusicVolume(int volume);
	void PlaySFX(Sound sfx);
	void SetSFXVolume(std::string id, int volume);
	void LoadSound();

	void Clean();

private:

	static SoundManager* _soundManagerInstance;

	std::map<std::string, Mix_Chunk*> _sfxs;
	std::map<std::string, Mix_Music*> _musics;

};