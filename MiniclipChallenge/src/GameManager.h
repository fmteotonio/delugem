#pragma once

class GameManager {
public:
	static GameManager* Instance();
	
	int level();
	int score();

	void LevelUp();
	void AddScore(int score);
	void Reset();

private:
	static GameManager* sGameManagerInstance_;

	int level_ = 1;
	int score_ = 0;
};