#include "EndLine.h"

#include "../TextureManager.h"

const char* EndLine::cPath = "res/images/endline.png";
const int EndLine::cW =      1;
const int EndLine::cH =      160;

EndLine::EndLine(Position pos) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);

	AddAnimation("Default", new Animation(0, 3, 0, 60));

	AnimatedGameObject::Init(pos, cW, cH, objTexture, "Default", true);
}