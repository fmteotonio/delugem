#include "StaticImage.h"

#include "../../TextureManager.h"

const char* StaticImage::cAnimDefault = "Default";

StaticImage::StaticImage(Position pos, Dimensions dim, std::string filename) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(filename);

	AddAnimation(cAnimDefault, new Animation(0, 0));

	AnimatedGameObject::Init(pos, dim, objTexture, cAnimDefault, false);
}