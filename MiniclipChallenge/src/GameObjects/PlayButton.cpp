#include "PlayButton.h"

#include "../Constants.h"
#include "../TextureManager.h"
#include "../InputHandler.h"

#include "../GameStates/TitleScreenState.h"

PlayButton::PlayButton(float x, float y) {
	clicked_ = false;

	SDL_Texture* objTexture = TextureManager::LoadTexture(SPR_PLAYBUTTON);
	GameObject::Init(x, y, PLAYBUTTON_W, PLAYBUTTON_H, objTexture, 0, 0);
}

bool PlayButton::clicked() {return clicked_;}

void PlayButton::Render() {
	GameObject::Render();
}

void PlayButton::Update(int deltaTime) {
	HandleInput();
}

void PlayButton::HandleInput() {
	if (InputHandler::Instance()->mouseLeft()) {
		//if click over me
		//transit to play
		clicked_ = true;
	}
}