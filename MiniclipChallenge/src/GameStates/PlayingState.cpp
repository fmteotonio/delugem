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

	gameObjects_.push_back(new ShadowedText(SCORETEXT_X, SCORETEXT_Y, Text::Align::MIDLEFT, FNT_M6X11, 16, "SCORE:", WHITE, BLACK));
	displayedScore_ = GameManager::Instance()->score();
	scoreValueText_ = new ShadowedText(SCOREVALUETEXT_X, SCOREVALUETEXT_Y, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedScore_), WHITE, BLACK);
	
	gameObjects_.push_back(new ShadowedText(LEVELTEXT_X, LEVELTEXT_Y, Text::Align::MIDLEFT, FNT_M6X11, 16, "LEVEL:", WHITE, BLACK));
	displayedLevel_ = GameManager::Instance()->level();
	levelValueText_ = new ShadowedText(LEVELVALUETEXT_X, LEVELVALUETEXT_Y, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedLevel_), WHITE, BLACK);

	gameObjects_.push_back(new Board(BOARD_START_X, BOARD_START_Y));
}

void PlayingState::Update(int deltaTime) {
	for (GameObject* gameObjectPointer : gameObjects_) {
		gameObjectPointer->Update(deltaTime);
	}
	//Check if score text needs update
	if (displayedScore_ != GameManager::Instance()->score()) {
		displayedScore_ = GameManager::Instance()->score();
		delete scoreValueText_;
		scoreValueText_ = new ShadowedText(SCOREVALUETEXT_X, SCOREVALUETEXT_Y, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedScore_), WHITE, BLACK);
	}
	//Check if level text needs update
	if (displayedLevel_ != GameManager::Instance()->level()) {
		displayedLevel_ = GameManager::Instance()->level();
		delete levelValueText_;
		levelValueText_ = new ShadowedText(LEVELVALUETEXT_X, LEVELVALUETEXT_Y, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedLevel_), WHITE, BLACK);
	}
}

void PlayingState::Render() {
	for (GameObject* gameObjectPointer : gameObjects_) {
		gameObjectPointer->Render();
	}
	scoreValueText_->Render();
	levelValueText_->Render();
}

void PlayingState::Clean() {
	for (GameObject* gameObjectPointer : gameObjects_) {
		delete gameObjectPointer;
	}
	delete scoreValueText_;
	delete levelValueText_;
}

std::string PlayingState::stateID() {
	return stateID_;
};