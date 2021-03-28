#include "StaticImage.h"

#include "../../TextureManager.h"

StaticImage::StaticImage(Position pos, int w, int h, std::string filename) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(filename);

	AddAnimation("Default", new Animation(0, 0));

	AnimatedGameObject::Init(pos, w, h, objTexture, "Default", false);
}