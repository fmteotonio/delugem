#pragma once

#include <map> 
#include <string>

#include <SDL_mixer.h>

class SoundManager {
public:
	enum class soundType {
		MUSIC, SFX
	};
	static SoundManager* Instance();

	bool Load(std::string filename, std::string id, soundType type, int volume);
	void PlayMusic(std::string id, int loop);
	void StopMusic();
	void SetMusicPosition(double position);
	void SetMusicVolume(int volume);
	void PlaySFX(std::string id, int loop);
	void SetSFXVolume(std::string id, int volume);

	void Clean();

private:
	static SoundManager* sSoundManagerInstance;

	std::map<std::string, Mix_Chunk*> _sfxs;
	std::map<std::string, Mix_Music*> _musics;
};