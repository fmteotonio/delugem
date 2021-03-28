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

int GameManager::GetScoreToNextLevel() {
	return 1000 * _level + 100 * (static_cast<int>(pow(2, _level - 1)) - 1);
}

void GameManager::AddScore(int gemNumber) {

	//_score += 10 * pow(2, gemNumber - 1);
	_score += 10 * gemNumber + (10 * (gemNumber - 2));

	while (_score >= GetScoreToNextLevel()) {
		SoundManager::Instance()->PlaySFX("LevelUp", false);
		++_level;
		if (_fillsLeft <= 9) {
			++_fillsLeft;
		}
	}
}

void GameManager::UseFill() {
	--_fillsLeft;
}

void GameManager::Reset() {
	_level = 1;
	_score = 0;
	_fillsLeft = 2;
}