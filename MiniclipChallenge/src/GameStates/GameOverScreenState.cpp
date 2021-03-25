#include "GameOverScreenState.h"

#include "../Constants.h"
#include "../GameObjects/ForegroundStrip.h"
#include "../GameObjects/Button.h"
#include "../GameObjects/ShadowedText.h"
#include "../Game.h"
#include "PlayingState.h"
#include "TitleScreenState.h"

const std::string GameOverScreenState::stateID_ = "GAMEOVERSCREEN";

void GameOverScreenState::Init() {
	gameObjects_.push_back(new ForegroundStrip(0, 0));
	gameObjects_.push_back(new ForegroundStrip(0, SCREEN_HEIGHT-FOREGROUNDSTRIP_H));

	gameObjects_.push_back(new ShadowedText(SCREEN_WIDTH/2, SCREEN_HEIGHT/2-50, Text::Align::MID, FNT_M6X11, 32, "GAME OVER", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 30, Text::Align::MID, FNT_M3X6, 16, "The Gems always win in the end.", WHITE, BLACK));
	
	float bXR = SCREEN_WIDTH / 2 - 60 - BIGBUTTON_W/2;
	float bXE = SCREEN_WIDTH / 2 + 60 - BIGBUTTON_W/2;
	float bY = 140;
	gameObjects_.push_back(playAgainButton_ = new Button(bXR, bY, BIGBUTTON_W, BIGBUTTON_H, SPR_BIGBUTTON));
	playAgainButton_->AddContent(new ShadowedText(bXR + BIGBUTTON_W / 2, bY + BIGBUTTON_H / 2, Text::Align::MID, FNT_M6X11, 16, "PLAY AGAIN", WHITE, BLACK));
	
	gameObjects_.push_back(exitButton_ = new Button(bXE, bY, BIGBUTTON_W, BIGBUTTON_H, SPR_BIGBUTTON));
	exitButton_->AddContent(new ShadowedText(bXE + BIGBUTTON_W / 2, bY + BIGBUTTON_H / 2, Text::Align::MID, FNT_M6X11, 16, "EXIT GAME", WHITE, BLACK));
}

void GameOverScreenState::Update(int deltaTime) {
	for (GameObject* gameObjectPointer : gameObjects_) {
		gameObjectPointer->Update(deltaTime);
	}
	if (playAgainButton_->buttonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->gameStateMachine()->changeState(new PlayingState());
		return;
	}
	if (exitButton_->buttonState() == Button::ButtonState::PRESS_ACTION)
		Game::Instance()->gameStateMachine()->changeState(new TitleScreenState());
}

void GameOverScreenState::Render() {
	for (GameObject* gameObjectPointer : gameObjects_) {
		gameObjectPointer->Render();
	}
}

void GameOverScreenState::Clean() {
	for (GameObject* gameObject : gameObjects_) {
		gameObject->Clean();
		delete gameObject;
	}
}

std::string GameOverScreenState::stateID() {
	return stateID_;
};
