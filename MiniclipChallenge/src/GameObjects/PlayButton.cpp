#include "PlayButton.h"

#include "../Constants.h"
#include "../TextureManager.h"
#include "../InputHandler.h"

#include "../GameStates/TitleScreenState.h"

#include "PlayButtonText.h"

PlayButton::PlayButton(float x, float y) {
	clicked_ = false;

	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(SPR_PLAYBUTTON);

	GameObject::Init(x, y, PLAYBUTTON_W, PLAYBUTTON_H, objTexture, new Animation("Still", 0, 0));

	//Components:
	playText_ = new PlayButtonText(x + PLAYBUTTON_W / 2, y + PLAYBUTTON_H/2);
}

bool PlayButton::clicked() {return clicked_;}

void PlayButton::Render() {
	GameObject::Render();
	//Components:
	playText_->Render();
}

void PlayButton::Update(int deltaTime) {
	HandleInput();
	//Components:
	playText_->Update(deltaTime);
}

void PlayButton::HandleInput() {
	if (InputHandler::Instance()->mouseLeft()) {
		//if click over me
		clicked_ = true;
	}
}

void PlayButton::Clean() {
	//Components:
	playText_->Clean();
	delete playText_;
}