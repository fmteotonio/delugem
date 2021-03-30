#pragma once

#include <map> 
#include <string>

#include <SDL_ttf.h>

class TextureManager {
public:
	static TextureManager* Instance();

	SDL_Texture* LoadTexture(std::string filename);
	SDL_Texture* LoadText(std::string filename, int size, std::string text, SDL_Color color);

	void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);

	void CleanTexture(std::string textureID);
	void CleanText(std::string textID);
	void CleanFont(std::string fontID);
	void CleanAllTextures();
	void CleanAllText();
	void CleanAllFonts();
	void CleanAll();
	

private:
	static TextureManager* _textureManagerInstance;

	std::map<std::string, SDL_Texture*> _objTextures;
	std::map<std::string, SDL_Texture*> _textTextures;
	std::map<std::string, TTF_Font*> fonts_;
	typedef std::map<std::string, SDL_Texture*> textureMap;
	typedef std::map<std::string, TTF_Font*> fontMap;

	TTF_Font* LoadFont(std::string filename, int size);
};