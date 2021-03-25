#pragma once

class GameManager {
public:
	static GameManager* Instance();
	
	int level();
	int score();
	int fillsLeft();
	int timePerColumn();

	void AddScore(int gemNumber);
	void useFill();
	void Reset();

private:
	static GameManager* sGameManagerInstance_;

	int level_ = 1;
	int score_ = 0;
	int fillsLeft_ = 2;
};