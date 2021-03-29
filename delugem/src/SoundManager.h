#pragma once

#include <map> 
#include <string>

#include <SDL_mixer.h>

class SoundManager {
public:

	enum class soundType {
		MUSIC, SFX
	};

	static const int cAudioFrequency;
	static const int cAudioChannelNumber;
	static const int cAudioChunkSize;

	static SoundManager* Instance();

	void Load(std::string filename, std::string id, soundType type, int volume);
	void PlayMusic(std::string id, int loop);
	void StopMusic();
	void SetMusicVolume(int volume);
	void PlaySFX(std::string id);
	void SetSFXVolume(std::string id, int volume);

	void Clean();

private:

	static SoundManager* _soundManagerInstance;

	std::map<std::string, Mix_Chunk*> _sfxs;
	std::map<std::string, Mix_Music*> _musics;

};