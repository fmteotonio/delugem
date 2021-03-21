#pragma once

#include <vector>
#include <random>

#include "Gem.h"
#include "GameObject.h"

class Board : public GameObject {
public:
	Board(float x, float y);
	
	void Update(int deltaTime);
	void HandleInput();
	void Render();

	int getNextGemID();
	void makeNewColumn();
	void clickPiece(Sint32 mouseX, Sint32 mouseY);
	void moveBoard(float x);
	void searchGemGroup(int gX, int gY);
	void eraseGem(int gX, int gY);

private:
	int gemID_;
	int scrollSpeed_;
	bool hasClicked_;
	std::default_random_engine generator_;
	std::vector<std::vector<Gem>> boardGems_;
};