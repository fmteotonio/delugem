#include "EndLine.h"

#include "../Constants.h"
#include "../TextureManager.h"

EndLine::EndLine(float x, float y) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(SPR_ENDLINE);

	addAnimation("Default", new Animation(0, 3, 0, 60));

	AnimatedGameObject::Init(x, y, ENDLINE_W, ENDLINE_H, objTexture, "Default", true);
}