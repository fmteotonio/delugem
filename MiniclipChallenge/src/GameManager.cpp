#include "GameManager.h"

#include "Constants.h"
#include "SoundManager.h"

#include <cmath>

//TEMP INCLUDE 
#include <iostream>

GameManager* GameManager::sGameManagerInstance = nullptr;

const int GameManager::cColumnTime = 10000;
const float GameManager::cColumnTimeMultiplier = 0.95f;
const int GameManager::cEndGemsMargin = 4;
const int GameManager::cStartColumns = 13;

int GameManager::GetLevel() { return _level; }
int GameManager::GetScore() { return _score; }
int GameManager::GetFillsLeft() { return _fillsLeft; }


int GameManager::TimePerColumn() {
	return cColumnTime * pow(cColumnTimeMultiplier, GameManager::Instance()->GetLevel() - 1);
}

GameManager* GameManager::Instance() {
	if (!sGameManagerInstance) {
		sGameManagerInstance = new GameManager();
	}
	return sGameManagerInstance;
}

void GameManager::AddScore(int gemNumber) {

	_score += 10 * pow(2, gemNumber - 1);

	while (_score >= 1000 * _level + 100 * (static_cast<int>(pow(2, _level-1))-1) ) {
		SoundManager::Instance()->PlaySFX("LevelUp", false);
		++_level;
		if (_fillsLeft <= 9) {
			++_fillsLeft;
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

void GameManager::UseFill() {
	--_fillsLeft;
}

void GameManager::Reset() {
	_level = 1;
	_score = 0;
	_fillsLeft = 2;
}