#include "GameManager.h"

#include "Constants.h"

#include <cmath>

//TEMP INCLUDE 
#include <iostream>

GameManager* GameManager::sGameManagerInstance_ = nullptr;

int GameManager::level() { return level_; }
int GameManager::score() { return score_; }
int GameManager::fillsLeft() { return fillsLeft_; }

int GameManager::timePerColumn() {
	return BOARD_COLUMNTIME * pow(BOARD_CTIMEMULTIP, GameManager::Instance()->level() - 1);
}

GameManager* GameManager::Instance() {
	if (!sGameManagerInstance_) {
		sGameManagerInstance_ = new GameManager();
	}
	return sGameManagerInstance_;
}

void GameManager::AddScore(int gemNumber) {

	score_ += 10 * pow(2, gemNumber - 1);

	while (score_ >= 1000 * level_ + 100 * (int(pow(2, level_-1))-1) ) {
		++level_;
		if (fillsLeft_ <= 9) {
			++fillsLeft_;
		}
	}
		
	//1 - 1000  = 1000 +     0
	//2 - 2100  = 2000 +   100
	//3 - 3200  = 3000 +   200
	//4 - 4400  = 4000 +   400
	//5 - 5800  = 5000 +   800
	//6 - 7600  = 6000 +  1600
	//7 - 10200 = 7000 +  3200
	//8 - 14400 = 8000 +  6400
	//9 - 21800 = 9000 + 12800
}

void GameManager::useFill() {
	--fillsLeft_;
}

void GameManager::Reset() {
	level_ = 1;
	score_ = 0;
	fillsLeft_ = 2;
}