#include "EndLine.h"

#include "../Constants.h"
#include "../TextureManager.h"

const char* EndLine::cPath = "res/images/endline.png";
const int EndLine::cW =      1;
const int EndLine::cH =      160;

EndLine::EndLine(float x, float y) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);

	AddAnimation("Default", new Animation(0, 3, 0, 60));

	AnimatedGameObject::Init(x, y, cW, cH, objTexture, "Default", true);
}