#pragma once

#include <SDL_mixer.h>

#include <map> 
#include <string>

class SoundManager {
public:
	enum class soundType {
		MUSIC, SFX
	};

	SoundManager();
	static SoundManager* Instance();

	bool Load(std::string filename, std::string id, soundType type, int volume);
	void playMusic(std::string id, int loop);
	void setMusicPosition(double position);
	void setMusicVolume(int volume);
	void playSFX(std::string id, int loop);
	void setSFXVolume(std::string id, int volume);

	void Clean();

private:
	static SoundManager* sSoundManagerInstance_;

	std::map<std::string, Mix_Chunk*> sfxs_;
	std::map<std::string, Mix_Music*> musics_;
};