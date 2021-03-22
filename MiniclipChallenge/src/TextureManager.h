#pragma once

#include "Game.h"

#include <SDL_ttf.h>

#include <map> 

class TextureManager {
public:
	static TextureManager* Instance();

	SDL_Texture* LoadTexture(std::string filename);
	SDL_Texture* LoadText(std::string filename, int size, std::string text, Uint8 r, Uint8 g, Uint8 b);

	void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);

	void Clean();
private:
	static TextureManager* sTextureManagerInstance_;

	std::map<std::string, SDL_Texture*> objTextures_;
	std::map<std::string, SDL_Texture*> textTextures_;
	std::map<std::string, TTF_Font*> fonts_;
	typedef std::map<std::string, SDL_Texture*> textureMap;
	typedef std::map<std::string, TTF_Font*> fontMap;

	TTF_Font* LoadFont(std::string filename, int size);

	bool temp;
};