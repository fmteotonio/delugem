#include "TitleScreenState.h"

#include "../Constants.h"
#include "../GameObjects/Background.h"
#include "../GameObjects/ForegroundStrip.h"
#include "../GameObjects/Button.h"
#include "../GameObjects/Text.h"
#include "../Game.h"
#include "PlayingState.h"

const std::string TitleScreenState::stateID_ = "TITLESCREEN";

void TitleScreenState::Init() {
	gameObjects_.push_back(new Background(0, 0));
	gameObjects_.push_back(new ForegroundStrip(0, 0));
	gameObjects_.push_back(new ForegroundStrip(0, SCREEN_HEIGHT-FOREGROUNDSTIRP_H));

	
	int bX = SCREEN_WIDTH / 2 - PLAYBUTTON_W / 2;
	int bY = SCREEN_HEIGHT / 2 - PLAYBUTTON_H / 2;
	int bW = PLAYBUTTON_W;
	int bH = PLAYBUTTON_H;
	
	GameObject* playButtonText = new Text(bX+bW/2, bY+bH/2, Text::Align::MID, FNT_M6X11, 16, "START GAME!", WHITE);
	GameObject* playButtonTextShadow = new Text(bX+bW/2+1, bY+bH/2+1, Text::Align::MID, FNT_M6X11, 16, "START GAME!", BLACK);
	gameObjects_.push_back(playButton_ = new Button(bX, bY, bW, bH, SPR_PLAYBUTTON));
	playButton_->AddContent(playButtonTextShadow);
	playButton_->AddContent(playButtonText);

}

void TitleScreenState::Update(int deltaTime) {
	for (GameObject* gameObjectPointer : gameObjects_) {
		gameObjectPointer->Update(deltaTime);
	}
	if (playButton_->buttonState() == Button::ButtonState::PRESS_ACTION)
		Game::Instance()->gameStateMachine()->changeState(new PlayingState());
}

void TitleScreenState::Render() {
	for (GameObject* gameObjectPointer : gameObjects_) {
		gameObjectPointer->Render();
	}
}

void TitleScreenState::Clean() {
	for (GameObject* gameObjectPointer : gameObjects_) {
		delete gameObjectPointer;
	}
}

std::string TitleScreenState::stateID() {
	return stateID_;
};
