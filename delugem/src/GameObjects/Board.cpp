#include "Board.h"

#include "../InputHandler.h"
#include "../TextureManager.h"
#include "../SoundManager.h"
#include "../GameManager.h"

#include <chrono>
#include <functional>

const int Board::cColumnSize = 10;

Board::Board(Position pos, bool isPlayable) {
	GameObject::Init(pos);
	_generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	_isPlayable = isPlayable;
}

std::vector<std::vector<Gem*>> Board::GetBoardGems() {
	return _boardGems;
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

	int conv_x = static_cast<int>(floor((InputHandler::Instance()->GetMouseX() - _pos.x) / Gem::cDim.w));
	int conv_y = static_cast<int>(floor(cColumnSize - (InputHandler::Instance()->GetMouseY() - _pos.y) / Gem::cDim.h));
	bool isHovered = conv_x >= 0 && conv_x < _boardGems.size() && conv_y >= 0 && conv_y < _boardGems.at(conv_x).size();


	//Release any previous Highlight
	if (_lastHoveredGem != nullptr && _lastHoveredGem->GetGemState() == Gem::GemState::HOVERED) {
		_lastHoveredGem->TransitState(Gem::GemState::DEFAULT);
		_lastHoveredGem = nullptr;
	}
	
	//If hovering a gem...
	if (isHovered) {
		Gem* gem = _boardGems.at(conv_x).at(conv_y);
		//...highlight if it is stopped.
		if (gem->GetGemState() == Gem::GemState::DEFAULT && !gem->isMoving(true, true)) {
			gem->TransitState(Gem::GemState::HOVERED);
			_lastHoveredGem = gem;
		}
		//Only once per click and if gem is not moving horizontally
		if (InputHandler::Instance()->GetMouseLeft() && !_hasClicked && !gem->isMoving(true, false)) {
			int gemsFound = SearchGemGroup(conv_x, conv_y);
			if (gemsFound > 1)
				GameManager::Instance()->AddScore(gemsFound);
		}				
	}
	if (InputHandler::Instance()->GetMouseLeft() && !_hasClicked) 
		_hasClicked = true;
	if (!InputHandler::Instance()->GetMouseLeft() && _hasClicked)
		_hasClicked = false;

	//----------------------------------------------------
}

void Board::Render() {

	//Does not render itself
	
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

int Board::NextGemID() {
	return ++_nextGemID;
}

void Board::AddNewColumns(int numberOfColumns) {
	for (int i = 0; i < numberOfColumns; i++) {
		std::vector<Gem*> newColumn;
		_boardGems.push_back(newColumn);
	}
}

std::vector<Gem*> Board::AddGem(int gX, int gemNumber) {

	std::uniform_int_distribution<int> distribution(0, Gem::cNumberOfColors - 1);
	std::vector<Gem*> producedGems;

	for (int i = 0; i < gemNumber; i++) {
		Gem::GemColor color = Gem::GemColor(distribution(_generator));

		Gem* newGem = new Gem(
			color,
			{ _pos.x + gX * Gem::cDim.w,
			_pos.y + (cColumnSize - _boardGems.at(gX).size() - 1) * Gem::cDim.h },
			NextGemID()
		);
		_boardGems.at(gX).push_back(newGem);
		producedGems.push_back(newGem);
	}
	return producedGems;
}

void Board::PushColumn(int n) {

	SoundManager::Instance()->PlaySFX("PushColumn",false);

	for (int aux = 0; aux < n; ++aux) {
		AddNewColumns(1);
		AddGem(_boardGems.size()-1, cColumnSize);
	}
	//Move board and all gems to the left
	_pos.x -= Gem::cDim.w * n;
	for (std::vector<Gem*> column : _boardGems) {
		for (Gem* gem : column) {
			gem->Move({ static_cast<float>(-Gem::cDim.w * n), 0 });
		}
	}
}

bool Board::FillBoard() {

	int maxGapHeight = 0;
	if (GameManager::Instance()->GetFillsLeft() > 0) {
		std::vector<Gem*> createdGems;
		//Creates gems in their correct places
		for (int i = 0; i < _boardGems.size(); ++i) {
			
			int thisGapHeight = cColumnSize - _boardGems.at(i).size();
			
			std::vector<Gem*> newGems = AddGem(i, thisGapHeight);
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

void Board::DestroyAllGems(bool compressEmptyColumns) {
	for (int i = _boardGems.size() - 1; i >= 0; --i) {
		for (int ii = _boardGems.at(i).size() - 1; ii >= 0; --ii) {
				EraseGem(i, ii, compressEmptyColumns);
		}
	}
}

int Board::SearchGemGroup(int gX, int gY) {

	int gemNumber = 0;
	std::vector<int> toDelete = {};

	enum class dir{
		NONE, UP, DOWN, LEFT, RIGHT
	};
	
	//Recursive Lambda:
	//	-> adds ID of clicked group gems to "to_delete".
	//	-> returns gem number in clicked group.
	std::function<int(dir, Gem::GemColor, int, int)> recursion = [&recursion,&toDelete,this]
		(dir d, Gem::GemColor gemColor, int gX, int gY) {

		//Gem doesn't exist in board
		if (gX >= 0 && gX < _boardGems.size()) {
			if (gY >= 0 && gY < _boardGems.at(gX).size()) {

				Gem* this_gem = _boardGems.at(gX).at(gY);

				//Gem is not same Color - X
				//Gem is same color but already checked - X
				if (this_gem->GetGemColor() != gemColor || 
					std::find(toDelete.begin(), toDelete.end(), this_gem->GetId()) != toDelete.end()) {
					return 0;
				}
				//Else add gem to delete.
				else {
					toDelete.push_back(this_gem->GetId());
					//Does not search in the same direction it came from.
					return 1 +
						(d==dir::LEFT  ? 0 : recursion(dir::RIGHT, gemColor, gX + 1, gY)) +
						(d==dir::RIGHT ? 0 : recursion(dir::LEFT,  gemColor, gX - 1, gY)) +
						(d==dir::DOWN  ? 0 : recursion(dir::UP,    gemColor, gX, gY + 1)) +
						(d==dir::UP    ? 0 : recursion(dir::DOWN,  gemColor, gX, gY - 1));
				}
			}
		}
		return 0;
	};

	gemNumber = recursion(dir::NONE, _boardGems.at(gX).at(gY)->GetGemColor(), gX, gY);

	if (gemNumber > 1) {
		
		SoundManager::Instance()->PlaySFX("Break",0);
		
		for (int i = _boardGems.size() - 1; i >= 0; --i) {
			for (int ii = _boardGems.at(i).size() - 1; ii >= 0; --ii) {
				if (std::find(toDelete.begin(), toDelete.end(), _boardGems.at(i).at(ii)->GetId()) != toDelete.end()) {
					EraseGem(i, ii, true);
				}
			}
		}
	}
	return gemNumber;
}

void Board::EraseGem(int gX, int gY, bool compressEmptyColumns) {
	std::vector<Gem*>& column = _boardGems.at(gX);
	
	_beingDestroyedGems.push_back(column.at(gY));
	column.at(gY)->TransitState(Gem::GemState::BREAKING);
	column.erase(column.begin() + gY);

	//Move every Gem above
	for (int i = gY; i < column.size(); ++i) {
		column.at(i)->Move({ 0, static_cast<float>(Gem::cDim.h) });
	}

	//Check if column empty
	if(compressEmptyColumns && column.empty()){
		_boardGems.erase(_boardGems.begin() + gX);

		//Move Board Origin
		_pos.x += Gem::cDim.w;

		//Move all left-hand gems.
		for (int i = 0; i < gX; ++i) {
			for (Gem* gem : _boardGems.at(i)) {
				gem->Move({ static_cast<float>(Gem::cDim.w), 0 });
			}
		}
	}
}