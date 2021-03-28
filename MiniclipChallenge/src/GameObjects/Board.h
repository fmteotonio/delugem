#pragma once

#include <random>
#include <vector>

#include "Gem.h"
#include "GameObject.h"

class Board : public GameObject {
public:
	static const int cColumnSize;
	static const int cStartColumns;

	Board(Position pos, bool isPlayable);
	
	void Update(int deltaTime);
	void HandleInput();
	void Render();
	void Clean();

	std::vector<std::vector<Gem*>> GetBoardGems();

	int NextGemID();
	void PushColumn(int n);
	bool FillBoard();
	int SearchGemGroup(int gX, int gY);
	void AddNewColumns(int numberOfColumns);
	std::vector<Gem*> AddGem(int gX, int gemNumber);
	void EraseGem(int gX, int gY, bool compress);
	void DestroyAllGems(bool compressGems);
	
private:
	int _nextGemID = 0;
	bool _hasClicked = false;
	bool _isPlayable = true;

	std::default_random_engine _generator;

	std::vector<std::vector<Gem*>> _boardGems;
	std::vector<Gem*> _beingDestroyedGems;
	
	Gem* _lastHoveredGem = nullptr;
};