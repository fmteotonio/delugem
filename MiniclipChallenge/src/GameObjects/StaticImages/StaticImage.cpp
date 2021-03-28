#include "StaticImage.h"

#include "../../TextureManager.h"

StaticImage::StaticImage(Position pos, Dimensions dim, std::string filename) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(filename);

	AddAnimation("Default", new Animation(0, 0));

	AnimatedGameObject::Init(pos, dim, objTexture, "Default", false);
}