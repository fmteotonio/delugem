#include "GameManager.h"

GameManager* GameManager::sGameManagerInstance_ = nullptr;

int GameManager::level() { return level_; }
int GameManager::score() { return score_; }

GameManager* GameManager::Instance() {
	if (!sGameManagerInstance_) {
		sGameManagerInstance_ = new GameManager();
	}
	return sGameManagerInstance_;
}

void GameManager::LevelUp() {
	++level_;
}

void GameManager::AddScore(int score) {
	score_ += score;
}

void GameManager::Reset() {
	level_ = 1;
	score_ = 0;
}