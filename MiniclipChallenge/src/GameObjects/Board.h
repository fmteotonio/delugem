#pragma once

#include <vector>
#include <random>

#include "Gem.h"
#include "GameObject.h"
#include "../Constants.h"

class Board : public GameObject {
public:
	static const int cColumnSize;
	static const int cStartColumns;

	Board(float x, float y);
	
	void Update(int deltaTime);
	void HandleInput();
	void Render();
	void Clean();

	bool IsGameLost();

	int NextGemID();
	void PushColumn(int n);
	void FillBoard();
	void SearchGemGroup(int gX, int gY);
	void EraseGem(int gX, int gY);
	
private:
	int nextGemID_ = 0;
	bool hasClicked_ = false;
	bool isGameLost_ = false;


	std::default_random_engine generator_;
	std::vector<std::vector<Gem*>> boardGems_;
	std::vector<Gem*> beingDestroyedGems_;
	Gem* lastHoveredGem_ = nullptr;

};