#include "PlayButtonText.h"

#include "../Constants.h"
#include "../TextureManager.h"
#include "../InputHandler.h"

#include "../GameStates/TitleScreenState.h"

PlayButtonText::PlayButtonText(float x, float y) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadText("res/fonts/m6x11.ttf", 20, "Hello World.",0,0,0);

	int w;
	int h;
	SDL_QueryTexture(objTexture, NULL, NULL, &w, &h);

	GameObject::Init(x, y, w, h, objTexture, 0, 0);
}

void PlayButtonText::Render() {
	GameObject::Render();
}

void PlayButtonText::Update(int deltaTime) {
}