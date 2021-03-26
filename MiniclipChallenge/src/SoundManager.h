#pragma once

#include <SDL_mixer.h>

#include <map> 
#include <string>

class SoundManager {
public:
	enum class soundType {
		MUSIC, SFX
	};
	static SoundManager* Instance();

	bool Load(std::string filename, std::string id, soundType type, int volume);
	void PlayMusic(std::string id, int loop);
	void SetMusicPosition(double position);
	void SetMusicVolume(int volume);
	void PlaySFX(std::string id, int loop);
	void SetSFXVolume(std::string id, int volume);

	void Clean();

private:
	static SoundManager* sSoundManagerInstance_;

	std::map<std::string, Mix_Chunk*> sfxs_;
	std::map<std::string, Mix_Music*> musics_;
};