#include "ForegroundStrip.h"

#include "../Constants.h"
#include "../TextureManager.h"

ForegroundStrip::ForegroundStrip(float x, float y) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(SPR_FOREGROUNDSTRIP);
	GameObject::Init(x, y, FOREGROUNDSTRIP_W, FOREGROUNDSTRIP_H, objTexture, new Animation(0,0));
}

void ForegroundStrip::Render() {
	GameObject::Render();
}

void ForegroundStrip::Update(int deltaTime) {
	GameObject::Update(deltaTime);
}