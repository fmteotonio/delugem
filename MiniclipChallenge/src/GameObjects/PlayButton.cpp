#include "PlayButton.h"

#include "../Constants.h"
#include "../TextureManager.h"
#include "../InputHandler.h"

#include "../GameStates/TitleScreenState.h"

#include "PlayButtonText.h"

PlayButton::PlayButton(float x, float y) {

	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(SPR_PLAYBUTTON);

	GameObject::Init(x, y, PLAYBUTTON_W, PLAYBUTTON_H, objTexture, new Animation("Still", 0, 0));

	//Components:
	playText_ = new PlayButtonText(x + PLAYBUTTON_W / 2, y + PLAYBUTTON_H/2);
}

bool PlayButton::clicked() {return clicked_;}

void PlayButton::Update(int deltaTime) {
	HandleInput();
	playText_->Update(deltaTime);

	GameObject::Update(deltaTime);
}

void PlayButton::HandleInput() {
	if (InputHandler::Instance()->mouseLeft()) {
		//if click over me
		clicked_ = true;
	}
}

void PlayButton::Render() {
	playText_->Render();

	GameObject::Render();
}

void PlayButton::Clean() {
	playText_->Clean();
	delete playText_;

	GameObject::Clean();
}