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

	Board(float x, float y, bool isPlayable);
	
	void Update(int deltaTime);
	void HandleInput();
	void Render();
	void Clean();

	int NextGemID();
	void PushColumn(int n);
	bool FillBoard();
	int SearchGemGroup(int gX, int gY);
	void AddColumn();
	Gem* AddGem(int gX);
	void EraseGem(int gX, int gY, bool compress);
	void DestroyAllGems();
	

	//TEMP PUBLIC
	std::vector<std::vector<Gem*>> boardGems_;
	std::vector<Gem*> beingDestroyedGems_;

private:
	int nextGemID_ = 0;
	bool hasClicked_ = false;
	bool isPlayable_ = true;

	std::default_random_engine generator_;
	
	
	Gem* lastHoveredGem_ = nullptr;
};