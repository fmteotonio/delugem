#include "TitleScreenState.h"

#include "../Constants.h"
#include "../GameObjects/ForegroundStrip.h"
#include "../GameObjects/Button.h"
#include "../GameObjects/ShadowedText.h"
#include "../Game.h"
#include "../GameManager.h"
#include "../SoundManager.h"
#include "PlayingState.h"


const std::string TitleScreenState::stateID_ = "TITLESCREEN";

void TitleScreenState::Init() {

	GameManager::Instance()->Reset();

	gameObjects_.push_back(new ForegroundStrip(0, 0));
	gameObjects_.push_back(new ForegroundStrip(0, SCREEN_HEIGHT-FOREGROUNDSTRIP_H));

	
	int bX = SCREEN_WIDTH / 2 - BIGBUTTON_W / 2;
	int bY = SCREEN_HEIGHT / 2 - BIGBUTTON_H / 2;
	int bW = BIGBUTTON_W;
	int bH = BIGBUTTON_H;

	gameObjects_.push_back(playButton_ = new Button(bX, bY, bW, bH, SPR_BIGBUTTON));
	playButton_->AddContent(new ShadowedText(bX + bW / 2, bY + bH / 2, Text::Align::MID, FNT_M6X11, 16, "START GAME!", WHITE, BLACK));

}

void TitleScreenState::Update(int deltaTime) {
	for (GameObject* gameObjectPointer : gameObjects_) {
		gameObjectPointer->Update(deltaTime);
	}
	if (playButton_->buttonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->gameStateMachine()->changeState(new PlayingState());
		SoundManager::Instance()->playSFX("GameStart", false);
	}
		
}

void TitleScreenState::Render() {
	for (GameObject* gameObjectPointer : gameObjects_) {
		gameObjectPointer->Render();
	}
}

void TitleScreenState::Clean() {
	for (GameObject* gameObject : gameObjects_) {
		gameObject->Clean();
		delete gameObject;
	}
}

std::string TitleScreenState::stateID() {
	return stateID_;
};
