#include "Board.h"

#include "../InputHandler.h"
#include "../TextureManager.h"
#include "../SoundManager.h"
#include "../GameManager.h"

#include <chrono>
#include <functional>

//DEBUG
#include <iostream>

const int Board::cColumnSize = 10;
const int Board::cStartColumns = 13;

Board::Board(float x, float y) {
	GameObject::Init(x, y);

	generator_.seed(std::chrono::system_clock::now().time_since_epoch().count());

	columnTimer_ = new Timer(GameManager::Instance()->TimePerColumn(), true);

	//Should not be Board Dependant
	pushClock_ = new PushClock(100, 100, columnTimer_);

	PushColumn(cStartColumns);
}

bool Board::IsGameLost() {
	return isGameLost_;
}


void Board::Update(int deltaTime) {

	columnTimer_->Update(deltaTime);
	
	//Should not be Board Dependant
	pushClock_->Update();
	
	
	if (columnTimer_->HasRung()) {
		PushColumn(1);
	}

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

	int conv_x = int(floor((InputHandler::Instance()->GetMouseX() - x_) / Gem::cW));
	int conv_y = int(floor(cColumnSize - (InputHandler::Instance()->GetMouseY() - y_) / Gem::cH));
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
		if (InputHandler::Instance()->GetMouseLeft() && !hasClicked_) 
			SearchGemGroup(conv_x, conv_y);			
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
	pushClock_->Render();
}

void Board::Clean() {
	delete columnTimer_;
	for (std::vector<Gem*> column : boardGems_) {
		for (Gem* gem : column) {
			delete gem;
		}
	}
	for (size_t i = 0; i < beingDestroyedGems_.size(); ++i) {
		delete beingDestroyedGems_.at(i);
	}
	delete pushClock_;
}

int Board::NextGemID() {
	return ++nextGemID_;
}

void Board::PushColumn(int n) {

	SoundManager::Instance()->PlaySFX("PushColumn",false);

	for (int aux = 0; aux < n; ++aux) {
		std::uniform_int_distribution<int> distribution(0, Gem::cNumberOfColors - 1);

		std::vector<Gem*> newColumn;
		for (int i = 0; i < cColumnSize; ++i) {

			Gem::GemColor color = Gem::GemColor(distribution(generator_));

			Gem* newGem = new Gem(
				color,
				x_ + (float)boardGems_.size() * Gem::cW,
				y_ + ((float)cColumnSize - i - 1) * Gem::cH,
				NextGemID()
			);
			newColumn.push_back(newGem);
		}
		boardGems_.push_back(newColumn);
	}
	//Move all gems to the left
	x_ -= Gem::cW * n;
	for (std::vector<Gem*> column : boardGems_) {
		for (Gem* gem : column) {
			gem->Move(-Gem::cW * n, 0);
		}
	}
	columnTimer_->ResetTimer(GameManager::Instance()->TimePerColumn());
	
	if (x_ < GameManager::cEndGemsMargin * Gem::cW)
		isGameLost_ = true;
}

void Board::FillBoard() {
	if (GameManager::Instance()->GetFillsLeft() > 0) {

		int maxGapHeight = 0;
		std::vector<Gem*> createdGems;

		//Creates gems in their correct places
		for (int i = 0; i < boardGems_.size(); i++) {
			std::vector<Gem*>& column = boardGems_.at(i);

			int thisGapHeight = 0;

			while (column.size() < 10) {

				++thisGapHeight;
				maxGapHeight = std::max(maxGapHeight, thisGapHeight);

				std::uniform_int_distribution<int> distribution(0, Gem::cNumberOfColors - 1);

				Gem::GemColor color = Gem::GemColor(distribution(generator_));

				Gem* newGem = new Gem(
					color,
					x_ + i * Gem::cW,
					y_ + (cColumnSize - (float)column.size() - 1) * Gem::cH,
					NextGemID()
				);

				createdGems.push_back(newGem);
				column.push_back(newGem);
			}
		}
		//Vertical offset just enough so they fall from the top
		for (Gem* gem : createdGems) {
			gem->SetY(gem->GetY() - maxGapHeight * Gem::cH);
			gem->Move(0, maxGapHeight * Gem::cH);
		}
		if (createdGems.size() > 0) {
			SoundManager::Instance()->PlaySFX("Fill", false);
			GameManager::Instance()->UseFill();
		}
			
	}
}

void Board::SearchGemGroup(int gX, int gY) {

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
					EraseGem(i, ii);
				}
			}
		}
		//Update Score
		GameManager::Instance()->AddScore(gemNumber);
	}
}

void Board::EraseGem(int gX, int gY) {
	std::vector<Gem*>& column = boardGems_.at(gX);
	
	beingDestroyedGems_.push_back(column.at(gY));
	column.at(gY)->TransitState(Gem::GemState::BREAKING);
	column.erase(column.begin() + gY);

	//Update position for every Gem above
	for (int i = gY; i < column.size(); ++i) {
		column.at(i)->Move(0, Gem::cH);
	}

	//Check if column empty
	if (column.empty()) {
		boardGems_.erase(boardGems_.begin() + gX);

		//Move Board Origin
		x_ += Gem::cW;

		//Move all left-hand gems.
		for (int i = 0; i < gX; ++i) {
			for (Gem* gem : boardGems_.at(i)) {
				gem->Move(Gem::cW, 0);
			}
		}
	}
}