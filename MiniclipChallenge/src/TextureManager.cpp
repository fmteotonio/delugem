#include "TextureManager.h"

#include "Game.h"

#include <iostream>

TextureManager* TextureManager::sTextureManagerInstance_ = nullptr;

TextureManager* TextureManager::Instance() {
	if (!sTextureManagerInstance_) {
		sTextureManagerInstance_ = new TextureManager();
	}
	return sTextureManagerInstance_;
}

SDL_Texture* TextureManager::LoadTexture(std::string filename) {
	textureMap::iterator findResult = objTextures_.find(filename);

	if (findResult == objTextures_.end()) {

		//DEBUG
		std::cout << "Inserted new ObjectTexture: " << filename << "\n";

		SDL_Surface* tempSurface = IMG_Load(filename.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::Instance()->renderer(), tempSurface);
		SDL_FreeSurface(tempSurface);

		objTextures_.insert({ filename , texture });
		return texture;
	}
	else
		return findResult->second;
}

SDL_Texture* TextureManager::LoadText(std::string filename, int size, std::string text, SDL_Color color) {
	TTF_Font* font = LoadFont(filename, size);

	textureMap::iterator findResult = textTextures_.find(filename + std::to_string(size) + text + std::to_string(color.r) + std::to_string(color.g) + std::to_string(color.b));

	if (findResult == textTextures_.end()) {

		//DEBUG
		std::cout << "Inserted new TextTexture: " << filename + std::to_string(size) + text + std::to_string(color.r) + std::to_string(color.g) + std::to_string(color.b) << "\n";

		SDL_Surface* tempSurface = TTF_RenderText_Solid(font, text.c_str(), color);
		//SDL_Surface* tempSurface = TTF_RenderText_Blended(font, text.c_str(), { r,g,b });
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::Instance()->renderer(), tempSurface);
		SDL_FreeSurface(tempSurface);

		textTextures_.insert({ filename + std::to_string(size) + text + std::to_string(color.r) + std::to_string(color.g) + std::to_string(color.b), texture });
		return texture;
	}
	else
		return findResult->second;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::Instance()->renderer(), tex, &src, &dest);
}

void TextureManager::Clean(){
	for (auto textTexturePair : textTextures_) {
		if (textTexturePair.second != NULL) {
			std::cout << "Destroyed Texture: " << textTexturePair.first << "\n";
			SDL_DestroyTexture(textTexturePair.second);
		}
	}
	for (auto objTexturePair : objTextures_) {
		if (objTexturePair.second != NULL) {
			std::cout << "Destroyed Texture: " << objTexturePair.first << "\n";
			SDL_DestroyTexture(objTexturePair.second);
		}
	}
	for (auto fontPair : fonts_) {
		if (fontPair.second != NULL) {
			std::cout << "Destroyed Font: " << fontPair.first << "\n";
			TTF_CloseFont(fontPair.second);
		}
	}
	textTextures_.clear();
	objTextures_.clear();
	fonts_.clear();
}

TTF_Font* TextureManager::LoadFont(std::string filename, int size) {
	fontMap::iterator findResult = fonts_.find(filename + std::to_string(size));

	if (findResult == fonts_.end()) {

		//DEBUG
		std::cout << "Inserted new Font: " << filename + std::to_string(size) << "\n";

		TTF_Font* font = TTF_OpenFont(filename.c_str(), size);
		fonts_.insert({ filename + std::to_string(size), font });
		return font;
	}
	else
		return findResult->second;
}