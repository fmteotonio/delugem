#include "TitleScreenState.h"

#include "../Constants.h"
#include "../GameObjects/Background.h"
#include "../Game.h"
#include "PlayingState.h"

const std::string TitleScreenState::stateID_ = "TITLESCREEN";

void TitleScreenState::Init() {
	gameObjects_.push_back(new Background(0, 0));
	gameObjects_.push_back(playButton_ = new PlayButton(SCREEN_WIDTH/2 - PLAYBUTTON_W/2, SCREEN_HEIGHT/2 - PLAYBUTTON_H / 2));
}

void TitleScreenState::Update(int deltaTime) {
	for (GameObject* gameObjectPointer : gameObjects_) {
		gameObjectPointer->Update(deltaTime);
	}
	if (playButton_->clicked())
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
