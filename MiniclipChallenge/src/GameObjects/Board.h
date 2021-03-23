#pragma once

#include <vector>
#include <random>

#include "Gem.h"
#include "GameObject.h"
#include "../Constants.h"
#include "../Timer.h"

class Board : public GameObject {
public:
	Board(float x, float y);
	
	void Update(int deltaTime);
	void HandleInput();
	void Render();
	void Clean();

	int getNextGemID();
	void makeNewColumn();
	void pushColumn();
	void moveBoard(float x);
	void searchGemGroup(int gX, int gY);
	void eraseGem(int gX, int gY);
	

private:
	int nextGemID_ = 0;
	int scrollSpeed_ = -BOARD_STARTINGSPD;
	bool hasClicked_ = false;

	Timer* columnTimer_;
	int timePerColumn = 5000;
	int timePassed = 0;

	std::default_random_engine generator_;
	std::vector<std::vector<Gem*>> boardGems_;
	std::vector<Gem*> beingDestroyedGems_;
	Gem* lastHoveredGem_ = nullptr;
};