#include "TextureManager.h"

#include "Game.h"

#include <iostream>

TextureManager* TextureManager::_textureManagerInstance = nullptr;

TextureManager* TextureManager::Instance() {
	if (!_textureManagerInstance) {
		_textureManagerInstance = new TextureManager();
	}
	return _textureManagerInstance;
}

SDL_Texture* TextureManager::LoadTexture(std::string filename) {
	std::map<std::string, SDL_Texture*>::iterator findResult = _objTextures.find(filename);

	if (findResult == _objTextures.end()) {

		SDL_Surface* tempSurface = IMG_Load(filename.c_str());
		if (!tempSurface) {
			std::cerr << "Image could not be loaded: " << SDL_GetError() << std::endl;
			return nullptr;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), tempSurface);
		SDL_FreeSurface(tempSurface);

		_objTextures.insert({ filename , texture });
		return texture;
	}
	else
		return findResult->second;
}

SDL_Texture* TextureManager::LoadText(std::string filename, int size, std::string text, SDL_Color color) {
	TTF_Font* font = LoadFont(filename, size);

	std::map<std::string, SDL_Texture*>::iterator findResult = 
		_textTextures.find(filename + std::to_string(size) + text + std::to_string(color.r) + std::to_string(color.g) + std::to_string(color.b));

	if (findResult == _textTextures.end()) {

		SDL_Surface* tempSurface = TTF_RenderText_Solid(font, text.c_str(), color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), tempSurface);
		SDL_FreeSurface(tempSurface);

		_textTextures.insert({ filename + std::to_string(size) + text + std::to_string(color.r) + std::to_string(color.g) + std::to_string(color.b), texture });
		return texture;
	}
	else		
		return findResult->second;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::Instance()->GetRenderer(), tex, &src, &dest);
}

void TextureManager::ReleaseTextures() {
	std::map<std::string, SDL_Texture*>::iterator it = _objTextures.begin();
	while (it != _objTextures.end()) {
		if (it->second != NULL) {
			SDL_DestroyTexture(it->second);
			it = _objTextures.erase(it);
		}
	}
}

void TextureManager::ReleaseTexts() {
	std::map<std::string, SDL_Texture*>::iterator it = _textTextures.begin();
	while (it != _textTextures.end()) {
		if (it->second != NULL) {
			SDL_DestroyTexture(it->second);
			it = _textTextures.erase(it);
		}
	}
}

void TextureManager::ReleaseFonts() {
	std::map<std::string, TTF_Font*>::iterator it = _fonts.begin();
	while (it != _fonts.end()) {
		if (it->second != NULL) {
			TTF_CloseFont(it->second);
			it = _fonts.erase(it);
		}
	}
}

void TextureManager::ReleaseAll(){
	ReleaseTextures();
	ReleaseTexts();
	ReleaseFonts();
}

void TextureManager::Clean() {
	ReleaseAll();
	delete _textureManagerInstance;
}

TTF_Font* TextureManager::LoadFont(std::string filename, int size) {
	std::map<std::string,TTF_Font*>::iterator findResult = _fonts.find(filename + std::to_string(size));

	if (findResult == _fonts.end()) {
		TTF_Font* font = TTF_OpenFont(filename.c_str(), size);
		if (!font) {
			std::cerr << "Font could not be loaded: " << SDL_GetError() << std::endl;
			return nullptr;
		}
		_fonts.insert({ filename + std::to_string(size), font });
		return font;
	}
	else
		return findResult->second;
}