#include "PlayButtonText.h"

#include "../Constants.h"
#include "../TextureManager.h"
#include "../InputHandler.h"

#include "../GameStates/TitleScreenState.h"

PlayButtonText::PlayButtonText(float x, float y) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadText(FNT_M6X11, 16, "PLAY GAME",255,255,255);

	int w, h;
	SDL_QueryTexture(objTexture, NULL, NULL, &w, &h);

	GameObject::Init(x-w/2, y-h/2+1, w, h, objTexture, new Animation("Still", 0, 0));
}

void PlayButtonText::Update(int deltaTime) {
	GameObject::Update(deltaTime);
}

void PlayButtonText::Render() {
	GameObject::Render();
}

void PlayButtonText::Clean() {
	GameObject::Clean();
}

