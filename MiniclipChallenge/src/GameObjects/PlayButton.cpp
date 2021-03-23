#include "PlayButton.h"

#include "../Constants.h"
#include "../TextureManager.h"
#include "../InputHandler.h"

#include "../GameStates/TitleScreenState.h"

#include "Text.h"

PlayButton::PlayButton(float x, float y) {

	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(SPR_PLAYBUTTON);

	defaultAnimation_ = new Animation(0, 0);
	pressedAnimation_ = new Animation(0, 1);

	GameObject::Init(x, y, PLAYBUTTON_W, PLAYBUTTON_H, objTexture, defaultAnimation_);

	//Components:
	playText_ = new Text(x_+w_/2, y_+h_/2, Text::Align::MID, FNT_M6X11, 16, "START GAME!", 255, 255, 255);
}

void PlayButton::Update(int deltaTime) {
	HandleInput();
	playText_->Update(deltaTime);

	GameObject::Update(deltaTime);
}

void PlayButton::HandleInput() {
	if (InputHandler::Instance()->mouseLeft() && playButtonState_ == PlayButtonState::DEFAULT) {
		int mouseX = InputHandler::Instance()->mouseX();
		int mouseY = InputHandler::Instance()->mouseY();
		if (mouseX > x_ && mouseX < x_+w_ && mouseY > y_ && mouseY < y_+h_) {
			TransitState(PlayButtonState::PRESSED);
		}
	}
	if (!InputHandler::Instance()->mouseLeft() && playButtonState_ == PlayButtonState::PRESSED) {
		int mouseX = InputHandler::Instance()->mouseX();
		int mouseY = InputHandler::Instance()->mouseY();
		if (mouseX > x_ && mouseX < x_ + w_ && mouseY > y_ && mouseY < y_ + h_) {
			TransitState(PlayButtonState::GAMESTATE_TOPLAYING);
		}
		else
			TransitState(PlayButtonState::DEFAULT);
	}
}

void PlayButton::Render() {
	GameObject::Render();
	playText_->Render();
}

void PlayButton::Clean() {
	playText_->Clean();
	delete defaultAnimation_;
	delete playText_;

	GameObject::Clean();
}

PlayButton::PlayButtonState PlayButton::playButtonState() {
	return playButtonState_;
}

bool PlayButton::TransitState(PlayButtonState newPlayButtonState) {
	switch (newPlayButtonState) {
		case PlayButtonState::DEFAULT:{
			if (playButtonState_ == PlayButtonState::PRESSED) {
				playButtonState_ = PlayButtonState::DEFAULT;
				animation_ = defaultAnimation_;
				return true;
			}
		}
		case PlayButtonState::PRESSED:{
			if (playButtonState_ == PlayButtonState::DEFAULT) {
				playButtonState_ = PlayButtonState::PRESSED;
				animation_ = pressedAnimation_;
				return true;
			}
		}
		case PlayButtonState::GAMESTATE_TOPLAYING: {
			if (playButtonState_ == PlayButtonState::PRESSED) {
				playButtonState_ = PlayButtonState::GAMESTATE_TOPLAYING;
				return true;
			}
		}
	}
	std::cout << "Illegal PlayButton Transition from " << int(playButtonState_) << " to " << int(newPlayButtonState) << "\n";
	return false;
}