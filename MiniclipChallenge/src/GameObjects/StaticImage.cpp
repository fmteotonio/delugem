#include "StaticImage.h"

#include "../Constants.h"
#include "../TextureManager.h"

StaticImage::StaticImage(float x, float y, int w, int h, std::string filename) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(filename);
	GameObject::Init(x, y, w, h, objTexture, new Animation(0,0));
}

void StaticImage::Render() {
	GameObject::Render();
}

void StaticImage::Update(int deltaTime) {
	GameObject::Update(deltaTime);
}