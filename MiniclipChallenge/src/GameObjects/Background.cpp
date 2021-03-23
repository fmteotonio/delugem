#include "Background.h"

#include "../Constants.h"
#include "../TextureManager.h"

Background::Background(float x, float y) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(SPR_BACKGROUND);
	Animation* animation = new Animation(0, 15, 0, 60);
	GameObject::Init(x, y, BACKGROUND_W, BACKGROUND_H, objTexture, animation);
	animation->Play();
}

void Background::Render() {
	GameObject::Render();
}

void Background::Update(int deltaTime) {
	GameObject::Update(deltaTime);
}