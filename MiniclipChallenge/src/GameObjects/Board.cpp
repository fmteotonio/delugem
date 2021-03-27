#include "Board.h"

#include "../InputHandler.h"
#include "../TextureManager.h"
#include "../SoundManager.h"
#include "../GameManager.h"

#include <chrono>
#include <functional>

const int Board::cColumnSize = 10;

Board::Board(float x, float y, bool isPlayable) {
	GameObject::Init(x, y);
	generator_.seed(std::chrono::system_clock::now().time_since_epoch().count());
	isPlayable_ = isPlayable;
}

std::vector<std::vector<Gem*>> Board::GetBoardGems() {
	return boardGems_;
}

void Board::Update(int deltaTime) {
	if (isPlayable_)
		HandleInput();

	for (std::vector<Gem*> column : boardGems_) {
		for (Gem* gem : column) {
			gem->Update(deltaTime);
		}
	}
	for (size_t i = 0; i < beingDestroyedGems_.size(); ++i) {
		beingDestroyedGems_.at(i)->Update(deltaTime);
		if (beingDestroyedGems_.at(i)->GetGemState() == Gem::GemState::TO_DESTROY) {
			delete beingDestroyedGems_.at(i);
			beingDestroyedGems_.erase(beingDestroyedGems_.begin() + i);
		}
	}
}

void Board::HandleInput() {

	int conv_x = static_cast<int>(floor((InputHandler::Instance()->GetMouseX() - x_) / Gem::cW));
	int conv_y = static_cast<int>(floor(cColumnSize - (InputHandler::Instance()->GetMouseY() - y_) / Gem::cH));
	bool isHovered = conv_x >= 0 && conv_x < boardGems_.size() && conv_y >= 0 && conv_y < boardGems_.at(conv_x).size();


	//Release any previous Highlight
	if (lastHoveredGem_ != nullptr && lastHoveredGem_->GetGemState() == Gem::GemState::HOVERED) {
		lastHoveredGem_->TransitState(Gem::GemState::DEFAULT);
		lastHoveredGem_ = nullptr;
	}
	
	//If hovering a gem...
	if (isHovered) {
		Gem* gem = boardGems_.at(conv_x).at(conv_y);
		//...highlight if it is stopped.
		if (gem->GetGemState() == Gem::GemState::DEFAULT && !gem->isMoving()) {
			gem->TransitState(Gem::GemState::HOVERED);
			lastHoveredGem_ = gem;
		}
		//Only once per click
		if (InputHandler::Instance()->GetMouseLeft() && !hasClicked_) {
			int gemsFound = SearchGemGroup(conv_x, conv_y);
			if (gemsFound > 1)
				GameManager::Instance()->AddScore(gemsFound);
		}				
	}
	if (InputHandler::Instance()->GetMouseLeft() && !hasClicked_) 
		hasClicked_ = true;
	if (!InputHandler::Instance()->GetMouseLeft() && hasClicked_)
		hasClicked_ = false;

	//----------------------------------------------------
}

void Board::Render() {

	//Does not render itself
	
	for (std::vector<Gem*> column : boardGems_) {
		for (Gem* gem : column) {
			gem->Render();
		}
	}
	for (Gem* gem : beingDestroyedGems_) {
		gem->Render();
	}
}

void Board::Clean() {
	
	for (std::vector<Gem*> column : boardGems_) {
		for (Gem* gem : column) {
			delete gem;
		}
	}
	for (size_t i = 0; i < beingDestroyedGems_.size(); ++i) {
		delete beingDestroyedGems_.at(i);
	}
}

int Board::NextGemID() {
	return ++nextGemID_;
}

void Board::AddNewColumns(int numberOfColumns) {
	for (int i = 0; i < numberOfColumns; i++) {
		std::vector<Gem*> newColumn;
		boardGems_.push_back(newColumn);
	}
}

std::vector<Gem*> Board::AddGem(int gX, int gemNumber) {

	std::uniform_int_distribution<int> distribution(0, Gem::cNumberOfColors - 1);
	std::vector<Gem*> producedGems;

	for (int i = 0; i < gemNumber; i++) {
		Gem::GemColor color = Gem::GemColor(distribution(generator_));

		Gem* newGem = new Gem(
			color,
			x_ + gX * Gem::cW,
			y_ + (cColumnSize - boardGems_.at(gX).size() - 1) * Gem::cH,
			NextGemID()
		);
		boardGems_.at(gX).push_back(newGem);
		producedGems.push_back(newGem);
	}
	return producedGems;
}

void Board::PushColumn(int n) {

	SoundManager::Instance()->PlaySFX("PushColumn",false);

	for (int aux = 0; aux < n; ++aux) {
		AddNewColumns(1);
		AddGem(boardGems_.size()-1, cColumnSize);
	}
	//Move board and all gems to the left
	x_ -= Gem::cW * n;
	for (std::vector<Gem*> column : boardGems_) {
		for (Gem* gem : column) {
			gem->Move(static_cast<float>(-Gem::cW * n), 0);
		}
	}
}

bool Board::FillBoard() {

	int maxGapHeight = 0;
	if (GameManager::Instance()->GetFillsLeft() > 0) {
		std::vector<Gem*> createdGems;
		//Creates gems in their correct places
		for (int i = 0; i < boardGems_.size(); ++i) {
			
			int thisGapHeight = cColumnSize - boardGems_.at(i).size();
			
			std::vector<Gem*> newGems = AddGem(i, thisGapHeight);
			createdGems.insert(createdGems.end(), newGems.begin(), newGems.end());

			maxGapHeight = std::max(maxGapHeight, thisGapHeight);

		}
		//Make new gems fall from over the Board
		for (Gem* gem : createdGems) {
			gem->MoveFrom(0, - maxGapHeight * Gem::cH);
		}
	}
	return maxGapHeight > 0;
}

void Board::DestroyAllGems() {
	for (int i = boardGems_.size() - 1; i >= 0; --i) {
		for (int ii = boardGems_.at(i).size() - 1; ii >= 0; --ii) {
				EraseGem(i, ii, false);
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
		if (gX >= 0 && gX < boardGems_.size()) {
			if (gY >= 0 && gY < boardGems_.at(gX).size()) {

				Gem* this_gem = boardGems_.at(gX).at(gY);

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

	gemNumber = recursion(dir::NONE, boardGems_.at(gX).at(gY)->GetGemColor(), gX, gY);

	if (gemNumber > 1) {
		
		SoundManager::Instance()->PlaySFX("Break",0);
		
		for (int i = boardGems_.size() - 1; i >= 0; --i) {
			for (int ii = boardGems_.at(i).size() - 1; ii >= 0; --ii) {
				if (std::find(toDelete.begin(), toDelete.end(), boardGems_.at(i).at(ii)->GetId()) != toDelete.end()) {
					EraseGem(i, ii, true);
				}
			}
		}
	}
	return gemNumber;
}

void Board::EraseGem(int gX, int gY, bool compressEmptyColumns) {
	std::vector<Gem*>& column = boardGems_.at(gX);
	
	beingDestroyedGems_.push_back(column.at(gY));
	column.at(gY)->TransitState(Gem::GemState::BREAKING);
	column.erase(column.begin() + gY);

	//Move every Gem above
	for (int i = gY; i < column.size(); ++i) {
		column.at(i)->Move(0, static_cast<float>(Gem::cH));
	}

	//Check if column empty
	if(compressEmptyColumns && column.empty()){
		boardGems_.erase(boardGems_.begin() + gX);

		//Move Board Origin
		x_ += Gem::cW;

		//Move all left-hand gems.
		for (int i = 0; i < gX; ++i) {
			for (Gem* gem : boardGems_.at(i)) {
				gem->Move(static_cast<float>(Gem::cW), 0);
			}
		}
	}
}