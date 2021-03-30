#include "Board.h"

#include "../InputHandler.h"
#include "../TextureManager.h"
#include "../SoundManager.h"
#include "../GameManager.h"

#include <chrono>
#include <functional>

Board::Board(Position pos, int columnSize, bool isPlayable) {
	_columnSize = columnSize;
	_isPlayable = isPlayable;

	_generator.seed(std::chrono::system_clock::now().time_since_epoch().count());

	GameObject::Init(pos);
}

int Board::NextGemID() {
	return ++_nextGemID;
}


std::vector<std::vector<Gem*>> Board::GetBoardGems() {
	return _boardGems;
}

/* Adds new empty column to board */
void Board::AddNewColumns(int numberOfColumns) {
	for (int i = 0; i < numberOfColumns; i++) {
		std::vector<Gem*> newColumn;
		_boardGems.push_back(newColumn);
	}
}

/* Adds gems to board in column index gX and returns a vector of pointers to all added gems */
std::vector<Gem*> Board::AddGems(int gX, int gemNumber) {

	std::uniform_int_distribution<int> distribution(0, Gem::cNumberOfColors - 1);
	std::vector<Gem*> producedGems;

	for (int i = 0; i < gemNumber; i++) {
		Gem::GemColor color = Gem::GemColor(distribution(_generator));

		Gem* newGem = new Gem(
			{ 
				_pos.x + gX * Gem::cDim.w,
				_pos.y + (_columnSize - _boardGems.at(gX).size() - 1) * Gem::cDim.h
			},
			color,
			NextGemID()
		);
		_boardGems.at(gX).push_back(newGem);
		producedGems.push_back(newGem);
	}
	return producedGems;
}


/* Adds n new columns to right side of the board and moves all gems to the left*/
void Board::PushColumns(int n) {

	SoundManager::Instance()->PlaySFX(SoundManager::cPushSound);

	for (int aux = 0; aux < n; ++aux) {
		AddNewColumns(1);
		AddGems(_boardGems.size()-1, _columnSize);
	}

	//Move left
	_pos.x -= Gem::cDim.w * n;
	for (std::vector<Gem*> column : _boardGems) {
		for (Gem* gem : column) {
			gem->MoveTo({ static_cast<float>(-Gem::cDim.w * n), 0 });
		}
	}
}

/* Fills all columns up to _columnSize. returns false if no gem was added */
bool Board::FillBoard() {

	int maxGapHeight = 0;
	if (GameManager::Instance()->GetFillsLeft() > 0) {
		std::vector<Gem*> createdGems;
		//Creates gems in their correct places
		for (int i = 0; i < _boardGems.size(); ++i) {
			
			int thisGapHeight = _columnSize - _boardGems.at(i).size();
			
			std::vector<Gem*> newGems = AddGems(i, thisGapHeight);
			createdGems.insert(createdGems.end(), newGems.begin(), newGems.end());

			maxGapHeight = std::max(maxGapHeight, thisGapHeight);

		}
		//Make new gems fall from over the Board
		for (Gem* gem : createdGems) {
			gem->MoveFrom({ 0, static_cast<float>(-maxGapHeight * Gem::cDim.h) });
		}
	}
	return maxGapHeight > 0;
}


void Board::BreakGem(int gX, int gY, bool compressEmptyColumns) {
	std::vector<Gem*>& column = _boardGems.at(gX);

	_beingDestroyedGems.push_back(column.at(gY));
	column.at(gY)->TransitState(Gem::GemState::BREAKING);
	column.erase(column.begin() + gY);

	//Move every Gem above
	for (int i = gY; i < column.size(); ++i) {
		column.at(i)->MoveTo({ 0, static_cast<float>(Gem::cDim.h) });
	}

	//Check if column empty
	if (compressEmptyColumns && column.empty()) {
		_boardGems.erase(_boardGems.begin() + gX);

		//Move Board Origin
		_pos.x += Gem::cDim.w;

		//Move all left-hand gems.
		for (int i = 0; i < gX; ++i) {
			for (Gem* gem : _boardGems.at(i)) {
				gem->MoveTo({ static_cast<float>(Gem::cDim.w), 0 });
			}
		}
	}
}

/* Sets gems with the provided ID's for destruction. 
   Can check and delete empty columns afterwards*/
void Board::BreakGems(std::vector<int> gemIDs, bool compressEmptyColumns) {
	
	for (int gX = _boardGems.size() - 1; gX >= 0; --gX) {
		for (int gY = _boardGems.at(gX).size() - 1; gY >= 0; --gY) {
			
			std::vector<int>::iterator findResult = std::find(gemIDs.begin(), gemIDs.end(), _boardGems.at(gX).at(gY)->GetId());

			if (findResult != gemIDs.end()) {
				gemIDs.erase(findResult);
				BreakGem(gX, gY, compressEmptyColumns);
			}
		}
	}
}

/* Sets all gems in for destruction. Can check and delete empty columns afterwards*/
void Board::BreakAllGems(bool compressEmptyColumns) {
	for (int i = _boardGems.size() - 1; i >= 0; --i) {
		for (int ii = _boardGems.at(i).size() - 1; ii >= 0; --ii) {
				BreakGem(i, ii, compressEmptyColumns);
		}
	}
}

/* Returns vector of gem ID's of adjacent gems to the [gX, gY] in the board. */
std::vector<int> Board::SearchGemGroup(int gX, int gY) {

	enum class dir{
		NONE, UP, DOWN, LEFT, RIGHT
	};
	
	std::vector<int> foundIDs;

	//Recursive Lambda:
	//	-> adds ID of clicked group gems to "to_delete".
	//	-> returns gem number in clicked group.
	std::function<void(dir, Gem::GemColor, int, int)> recursion = [&recursion,&foundIDs,this]
		(dir d, Gem::GemColor gemColor, int gX, int gY) {

		//Check if gem exists in board space
		if (gX >= 0 && gX < _boardGems.size()) {
			if (gY >= 0 && gY < _boardGems.at(gX).size()) {

				Gem* this_gem = _boardGems.at(gX).at(gY);

				//Gem is same Color and was not already checked
				if (this_gem->GetGemColor() == gemColor && 
				std::find(foundIDs.begin(), foundIDs.end(), this_gem->GetId()) == foundIDs.end()) {
					foundIDs.push_back(this_gem->GetId());
					//Does not search in the same direction it came from.
					if (d != dir::LEFT)  recursion(dir::RIGHT, gemColor, gX + 1, gY);
					if (d != dir::RIGHT) recursion(dir::LEFT, gemColor, gX - 1, gY);
					if (d != dir::DOWN)  recursion(dir::UP, gemColor, gX, gY + 1);
					if (d != dir::UP)    recursion(dir::DOWN, gemColor, gX, gY - 1);
				}

			}
		}
		return;
	};
	recursion(dir::NONE, _boardGems.at(gX).at(gY)->GetGemColor(), gX, gY);
	return foundIDs;
}


void Board::Update(int deltaTime) {
	if (_isPlayable)
		HandleInput();

	for (std::vector<Gem*> column : _boardGems) {
		for (Gem* gem : column) {
			gem->Update(deltaTime);
		}
	}

	for (size_t i = 0; i < _beingDestroyedGems.size(); ++i) {
		_beingDestroyedGems.at(i)->Update(deltaTime);
		if (_beingDestroyedGems.at(i)->GetGemState() == Gem::GemState::TO_DESTROY) {
			delete _beingDestroyedGems.at(i);
			_beingDestroyedGems.erase(_beingDestroyedGems.begin() + i);
		}
	}
}

void Board::HandleInput() {

	int convX = static_cast<int>(floor((InputHandler::Instance()->GetMouseX() - _pos.x) / Gem::cDim.w));
	int convY = static_cast<int>(floor(_columnSize - (InputHandler::Instance()->GetMouseY() - _pos.y) / Gem::cDim.h));
	bool isHovered = convX >= 0 && convX < _boardGems.size() && convY >= 0 && convY < _boardGems.at(convX).size();


	//Release any previous Highlight
	if (_lastHoveredGem != nullptr && _lastHoveredGem->GetGemState() == Gem::GemState::HOVERED) {
		_lastHoveredGem->TransitState(Gem::GemState::DEFAULT);
		_lastHoveredGem = nullptr;
	}

	//If hovering a gem...
	if (isHovered) {
		Gem* gem = _boardGems.at(convX).at(convY);
		//...highlight if it is stopped.
		if (gem->GetGemState() == Gem::GemState::DEFAULT && !gem->isMoving(true, true)) {
			gem->TransitState(Gem::GemState::HOVERED);
			_lastHoveredGem = gem;
		}
		//Only once per click and if gem is not moving horizontally
		if (InputHandler::Instance()->GetMouseLeft() && !_hasClicked && !gem->isMoving(true, false)) {
			std::vector<int> gemsFoundIds = SearchGemGroup(convX, convY);
			if (gemsFoundIds.size() > 1) {
				GameManager::Instance()->AddScore(gemsFoundIds.size());
				SoundManager::Instance()->PlaySFX(SoundManager::cBreakSound);
				BreakGems(gemsFoundIds, true);
			}
		}
	}
	if (InputHandler::Instance()->GetMouseLeft() && !_hasClicked)
		_hasClicked = true;
	else if (!InputHandler::Instance()->GetMouseLeft() && _hasClicked)
		_hasClicked = false;

	//----------------------------------------------------
}

void Board::Render() {
	for (std::vector<Gem*> column : _boardGems) {
		for (Gem* gem : column) {
			gem->Render();
		}
	}
	for (Gem* gem : _beingDestroyedGems) {
		gem->Render();
	}
}

void Board::Clean() {
	for (std::vector<Gem*> column : _boardGems) {
		for (Gem* gem : column) {
			delete gem;
		}
	}
	for (size_t i = 0; i < _beingDestroyedGems.size(); ++i) {
		delete _beingDestroyedGems.at(i);
	}
}