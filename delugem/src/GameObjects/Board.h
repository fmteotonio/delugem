#pragma once

#include <random>
#include <vector>

#include "Gem.h"
#include "GameObject.h"

class Board : public GameObject {
public:

	Board(Position pos, int columnSize, bool isPlayable);

	int NextGemID();
	std::vector<std::vector<Gem*>> GetBoardGems();

	void AddNewColumns(int numberOfColumns);
	std::vector<Gem*> AddGems(int gX, int gemNumber);
	void PushColumns(int n);
	bool FillBoard();
	void BreakGem(int gX, int gY, bool compressEmptyColumns);
	void BreakGems(std::vector<int> gemIDs, bool compressEmptyColumns);
	void BreakAllGems(bool compressEmptyColumns);
	std::vector<int> SearchGemGroup(int gX, int gY);

	void Update(int deltaTime);
	void Render();
	void Clean();

private:

	int _columnSize;
	bool _isPlayable;

	int _nextGemID = 0;
	bool _hasClicked = false;
	
	std::default_random_engine _generator;
	std::vector<std::vector<Gem*>> _boardGems;
	std::vector<Gem*> _beingDestroyedGems;	
	Gem* _lastHoveredGem = nullptr;

	void HandleInput();
};