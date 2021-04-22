#pragma once

class GameManager {
public:

	static const int cColumnTime;
	static const float cColumnTimeMultiplier;
	static const int cEndGemsMargin;
	static const int cStartColumns;

	static GameManager* Instance();

	int GetLevel();
	int GetScore();
	int GetFillsLeft();
	int GetScoreToNextLevel();
	int GetTimePerColumn();

	void AddScore(int gemNumber);
	void UseFill();
	void ResetGame();

	void Clean();

private:

	static GameManager* _gameManagerInstance;

	int _level;
	int _score;
	int _fillsLeft;

};