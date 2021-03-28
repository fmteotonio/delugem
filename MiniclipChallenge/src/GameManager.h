#pragma once

class GameManager {
public:
	static GameManager* Instance();

	static const int cColumnTime;
	static const float cColumnTimeMultiplier;
	static const int cEndGemsMargin;
	static const int cStartColumns;
	
	int GetLevel();
	int GetScore();
	int GetFillsLeft();

	int TimePerColumn();

	void AddScore(int gemNumber);
	void UseFill();
	void Reset();

private:
	static GameManager* sGameManagerInstance;

	int _level;
	int _score;
	int _fillsLeft;
};