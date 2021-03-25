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

	int level_;
	int score_;
	int fillsLeft_;
};