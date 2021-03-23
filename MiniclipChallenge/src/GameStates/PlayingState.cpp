#include "PlayingState.h"

#include "../GameObjects/Background.h"
#include "../GameObjects/ForegroundStrip.h"
#include "../GameObjects/Board.h"
#include "../GameObjects/Button.h"
#include "../GameObjects/Text.h"
#include "../Constants.h"

const std::string PlayingState::stateID_ = "PLAYING";

void PlayingState::Init() {
	gameObjects_.push_back(new Background(0, 0));
	gameObjects_.push_back(new ForegroundStrip(0, 0));
	gameObjects_.push_back(new ForegroundStrip(0, SCREEN_HEIGHT - FOREGROUNDSTIRP_H));

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