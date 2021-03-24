#include "EndLine.h"

#include "../Constants.h"
#include "../TextureManager.h"

EndLine::EndLine(float x, float y) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(SPR_ENDLINE);
	Animation* animation = new Animation(0, 3, 0, 60);
	GameObject::Init(x, y, ENDLINE_W, ENDLINE_H, objTexture, animation);
	animation->Play();
}

void EndLine::Render() {
	GameObject::Render();
}

void EndLine::Update(int deltaTime) {
	GameObject::Update(deltaTime);
}