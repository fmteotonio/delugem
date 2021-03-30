#include "GameManager.h"

#include <cmath>

#include "Constants.h"
#include "SoundManager.h"

GameManager* GameManager::_gameManagerInstance = nullptr;

const int GameManager::cColumnTime = 9500;
const float GameManager::cColumnTimeMultiplier = 0.95f;
const int GameManager::cEndGemsMargin = 4;
const int GameManager::cStartColumns = 13;

GameManager* GameManager::Instance() {
	if (!_gameManagerInstance) {
		_gameManagerInstance = new GameManager();
	}
	return _gameManagerInstance;
}

int GameManager::GetLevel() { 
	return _level; 
}

int GameManager::GetScore() { 
	return _score; 
}

int GameManager::GetFillsLeft() { 
	return _fillsLeft; 
}

int GameManager::GetScoreToNextLevel() {
	return 1000 * _level + 100 * (static_cast<int>(pow(2, _level)));
}

int GameManager::GetTimePerColumn() {
	return cColumnTime * pow(cColumnTimeMultiplier, GetLevel() - 1);
}

void GameManager::AddScore(int gemNumber) {
	_score += 10 * gemNumber + (10 * (gemNumber - 2));

	while (_score >= GetScoreToNextLevel()) {
		++_level;
	}
}

void GameManager::UseFill() {
	--_fillsLeft;
}

void GameManager::ResetGame() {
	_level = 1;
	_score = 0;
	_fillsLeft = 3;
}

void GameManager::Clean() {
	delete _gameManagerInstance;
}