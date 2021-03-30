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

		//DEBUG
		std::cout << "Inserted new ObjectTexture: " << filename << "\n";

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

		//DEBUG
		std::cout << "Inserted new TextTexture: " << filename + std::to_string(size) + text + std::to_string(color.r) + std::to_string(color.g) + std::to_string(color.b) << "\n";

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

void TextureManager::CleanTexture(std::string textureID) {
	auto findResult = _objTextures.find(textureID);
	if (findResult != _objTextures.end()) {
		std::cout << "Destroyed Texture: " << findResult->first << "\n";
		SDL_DestroyTexture(findResult->second);
		_objTextures.erase(findResult);
	}
}

void TextureManager::CleanText(std::string textID) {
	auto findResult = _textTextures.find(textID);
	if (findResult != _textTextures.end()) {
		std::cout << "Destroyed Text: " << findResult->first << "\n";
		SDL_DestroyTexture(findResult->second);
		_textTextures.erase(findResult);
	}
}

void TextureManager::CleanFont(std::string fontID) {
	auto findResult = fonts_.find(fontID);
	if (findResult != fonts_.end()) {
		std::cout << "Destroyed Font: " << findResult->first << "\n";
		TTF_CloseFont(findResult->second);
		fonts_.erase(findResult);
	}
}

void TextureManager::CleanAllTextures() {
	for (auto objTexturePair : _objTextures) {
		if (objTexturePair.second != NULL) {
			std::cout << "Destroyed Texture: " << objTexturePair.first << "\n";
			SDL_DestroyTexture(objTexturePair.second);
			_objTextures.erase(objTexturePair.first);
		}
	}
}
void TextureManager::CleanAllText() {
	for (auto textTexturePair : _textTextures) {
		if (textTexturePair.second != NULL) {
			std::cout << "Destroyed Texture: " << textTexturePair.first << "\n";
			SDL_DestroyTexture(textTexturePair.second);
			_textTextures.erase(textTexturePair.first);
		}
	}
}
void TextureManager::CleanAllFonts() {
	for (auto fontPair : fonts_) {
		if (fontPair.second != NULL) {
			std::cout << "Destroyed Font: " << fontPair.first << "\n";
			TTF_CloseFont(fontPair.second);
		}
	}
}

void TextureManager::CleanAll(){
	CleanAllTextures();
	CleanAllText();
	CleanAllFonts();
	delete _textureManagerInstance;
}

TTF_Font* TextureManager::LoadFont(std::string filename, int size) {
	fontMap::iterator findResult = fonts_.find(filename + std::to_string(size));

	if (findResult == fonts_.end()) {

		//DEBUG
		std::cout << "Inserted new Font: " << filename + std::to_string(size) << "\n";

		TTF_Font* font = TTF_OpenFont(filename.c_str(), size);
		if (!font) {
			std::cerr << "Font could not be loaded: " << SDL_GetError() << std::endl;
			return nullptr;
		}
		fonts_.insert({ filename + std::to_string(size), font });
		return font;
	}
	else
		return findResult->second;
}