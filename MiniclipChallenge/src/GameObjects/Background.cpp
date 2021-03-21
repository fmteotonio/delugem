#include "Background.h"

#include "../Constants.h"
#include "../TextureManager.h"

Background::Background(float x, float y) {
	SDL_Texture* objTexture = TextureManager::LoadTexture(SPR_BACKGROUND);
	GameObject::Init(x, y, BACKGROUND_W, BACKGROUND_H, objTexture, 0, 0);
}

void Background::Render() {
	GameObject::Render();
}

void Background::Update(int deltaTime) {
	GameObject::Update(deltaTime);
}