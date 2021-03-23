#include "PlayingState.h"

#include "../GameObjects/Background.h"
#include "../GameObjects/ForegroundStrip.h"
#include "../GameObjects/Board.h"
#include "../GameObjects/Button.h"
#include "../GameObjects/ShadowedText.h"
#include "../Constants.h"
#include "../GameManager.h"

const std::string PlayingState::stateID_ = "PLAYING";

void PlayingState::Init() {
	gameObjects_.push_back(new Background(0, 0));
	gameObjects_.push_back(new ForegroundStrip(0, 0));
	gameObjects_.push_back(new ForegroundStrip(0, SCREEN_HEIGHT - FOREGROUNDSTIRP_H));

	//Temp Score Text
	gameObjects_.push_back(new ShadowedText(7, 7, Text::Align::UPLEFT, FNT_M6X11, 16, "SCORE: 3000000" + std::to_string(GameManager::Instance()->score()), WHITE, BLACK));

	gameObjects_.push_back(new Board(BOARD_START_X, BOARD_START_Y));
}

void PlayingState::Update(int deltaTime) {
	for (GameObject* gameObjectPointer : gameObjects_) {
		gameObjectPointer->Update(deltaTime);
	}
}

void PlayingState::Render() {
	for (GameObject* gameObjectPointer : gameObjects_) {
		gameObjectPointer->Render();
	}
}

void PlayingState::Clean() {
	for (GameObject* gameObjectPointer : gameObjects_) {
		delete gameObjectPointer;
	}
}

std::string PlayingState::stateID() {
	return stateID_;
};