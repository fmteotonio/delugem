#include "PlayButton.h"

#include "../Constants.h"
#include "../TextureManager.h"
#include "../InputHandler.h"

#include "../GameStates/TitleScreenState.h"

#include "Text.h"

PlayButton::PlayButton(float x, float y) {

	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(SPR_PLAYBUTTON);

	defaultAnimation = new Animation(0, 0);
	pressedAnimation = new Animation(0, 1);

	GameObject::Init(x, y, PLAYBUTTON_W, PLAYBUTTON_H, objTexture, defaultAnimation);

	//Components:
	playText_ = new Text(x_+w_/2, y_+h_/2, Text::Align::MID, FNT_M6X11, 16, "START GAME!", 255, 255, 255);
}

bool PlayButton::clicked() {return clicked_;}

void PlayButton::Update(int deltaTime) {
	HandleInput();
	playText_->Update(deltaTime);

	GameObject::Update(deltaTime);
}

void PlayButton::HandleInput() {
	if (InputHandler::Instance()->mouseLeft() && playButtonState == PlayButtonState::DEFAULT) {
		int mouseX = InputHandler::Instance()->mouseX();
		int mouseY = InputHandler::Instance()->mouseY();
		if (mouseX > x_ && mouseX < x_+w_ && mouseY > y_ && mouseY < y_+h_) {
			playButtonState = PlayButtonState::PRESSED;
			animation_ = pressedAnimation;
		}
	}
	if (!InputHandler::Instance()->mouseLeft() && playButtonState == PlayButtonState::PRESSED) {
		int mouseX = InputHandler::Instance()->mouseX();
		int mouseY = InputHandler::Instance()->mouseY();
		if (mouseX > x_ && mouseX < x_ + w_ && mouseY > y_ && mouseY < y_ + h_) {
			clicked_ = true;
		}
		else
			playButtonState = PlayButtonState::DEFAULT;
			animation_ = defaultAnimation;
	}
}

void PlayButton::Render() {
	GameObject::Render();
	playText_->Render();
}

void PlayButton::Clean() {
	playText_->Clean();
	delete defaultAnimation;
	delete playText_;

	GameObject::Clean();
}