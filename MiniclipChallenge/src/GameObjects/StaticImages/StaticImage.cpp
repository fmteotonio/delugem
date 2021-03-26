#include "StaticImage.h"

#include "../../TextureManager.h"

StaticImage::StaticImage(float x, float y, int w, int h, std::string filename) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(filename);

	AddAnimation("Default", new Animation(0, 0));

	AnimatedGameObject::Init(x, y, w, h, objTexture, "Default", false);
}