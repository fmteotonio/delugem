#include "Background.h"

#include "../Constants.h"
#include "../TextureManager.h"

//DEBUG
#include <iostream>

Background::Background(float x, float y) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(SPR_BACKGROUND);

	addAnimation("Default", new Animation(0, 15, 0, 60));

	AnimatedGameObject::Init(x, y, BACKGROUND_W, BACKGROUND_H, objTexture, "Default", true);
}