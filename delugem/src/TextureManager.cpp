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
	textureMap::iterator findResult = _objTextures.find(filename);

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

	textureMap::iterator findResult = _textTextures.find(filename + std::to_string(size) + text + std::to_string(color.r) + std::to_string(color.g) + std::to_string(color.b));

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
	for (auto objTexturePair : _objTextures) {
		if (objTexturePair.second != NULL) {
			SDL_DestroyTexture(objTexturePair.second);
			_objTextures.erase(objTexturePair.first);
		}
	}
}
void TextureManager::ReleaseTexts() {
	for (auto textTexturePair : _textTextures) {
		if (textTexturePair.second != NULL) {
			SDL_DestroyTexture(textTexturePair.second);
			_textTextures.erase(textTexturePair.first);
		}
	}
}
void TextureManager::ReleaseFonts() {
	for (auto fontPair : _fonts) {
		if (fontPair.second != NULL) {
			TTF_CloseFont(fontPair.second);
			_fonts.erase(fontPair.first);
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
	fontMap::iterator findResult = _fonts.find(filename + std::to_string(size));

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