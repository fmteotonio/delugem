#include "EndLine.h"

#include "../TextureManager.h"

const char*      EndLine::cPath = "res/images/endline.png";
const Dimensions EndLine::cDim  = { 1,160 };

const char* EndLine::cAnimDefault = "Default";

EndLine::EndLine(Position pos) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);

	AddAnimation(cAnimDefault, new Animation(0, 3, 0, 60));

	AnimatedGameObject::Init(pos, cDim, objTexture, cAnimDefault, true);
}