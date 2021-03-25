#include "Board.h"

#include "../InputHandler.h"
#include "../TextureManager.h"
#include "../GameManager.h"

#include <chrono>
#include <functional>

//DEBUG
#include <iostream>

Board::Board(float x, float y) {
	GameObject::Init(x, y, 0, 0, nullptr, nullptr);

	generator_.seed(std::chrono::system_clock::now().time_since_epoch().count());


	columnTimer_ = new Timer(GameManager::Instance()->timePerColumn(), true);

	pushColumn(BOARD_STARTCOLUMNS);
}

bool Board::gameLost() {
	return gameLost_;
}


void Board::Update(int deltaTime) {

	columnTimer_->Update(deltaTime);
	if (columnTimer_->hasRung()) {
		pushColumn(1);
	}

	HandleInput();

	for (std::vector<Gem*> column : boardGems_) {
		for (Gem* gem : column) {
			gem->Update(deltaTime);
		}
	}
	for (size_t i = 0; i < beingDestroyedGems_.size(); ++i) {
		beingDestroyedGems_.at(i)->Update(deltaTime);
		if (beingDestroyedGems_.at(i)->gemState() == Gem::GemState::TO_DESTROY) {
			delete beingDestroyedGems_.at(i);
			beingDestroyedGems_.erase(beingDestroyedGems_.begin() + i);
		}
	}
}

void Board::HandleInput() {

	int conv_x = int(floor((InputHandler::Instance()->mouseX() - x_) / GEM_W));
	int conv_y = int(floor(BOARD_HEIGHT - (InputHandler::Instance()->mouseY() - y_) / GEM_H));
	bool isHovered = conv_x >= 0 && conv_x < boardGems_.size() && conv_y >= 0 && conv_y < boardGems_.at(conv_x).size();


	//Release any previous Highlight
	if (lastHoveredGem_ != nullptr && lastHoveredGem_->gemState() == Gem::GemState::HOVERED) {
		lastHoveredGem_->TransitState(Gem::GemState::DEFAULT);
		lastHoveredGem_ = nullptr;
	}
	
	//If hovering a gem...
	if (isHovered) {
		Gem* gem = boardGems_.at(conv_x).at(conv_y);
		//...highlight if it is stopped.
		if (gem->gemState() == Gem::GemState::DEFAULT && !gem->isMoving()) {
			gem->TransitState(Gem::GemState::HOVERED);
			lastHoveredGem_ = gem;
		}
		//Only once per click
		if (InputHandler::Instance()->mouseLeft() && !hasClicked_) 
			searchGemGroup(conv_x, conv_y);			
	}
	if (InputHandler::Instance()->mouseLeft() && !hasClicked_) 
		hasClicked_ = true;
	if (!InputHandler::Instance()->mouseLeft() && hasClicked_)
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
	delete columnTimer_;
	for (std::vector<Gem*> column : boardGems_) {
		for (Gem* gem : column) {
			delete gem;
		}
	}
	for (size_t i = 0; i < beingDestroyedGems_.size(); ++i) {
		delete beingDestroyedGems_.at(i);
	}
}

int Board::getNextGemID() {
	return ++nextGemID_;
}

void Board::pushColumn(int n) {
	for (int aux = 0; aux < n; ++aux) {
		std::uniform_int_distribution<int> distribution(0, GEM_TYPE_NUMBER - 1);

		std::vector<Gem*> newColumn;
		for (int i = 0; i < BOARD_HEIGHT; ++i) {

			Gem::GemColor color = Gem::GemColor(distribution(generator_));

			Gem* newGem = new Gem(
				color,
				x_ + (float)boardGems_.size() * GEM_W,
				y_ + ((float)BOARD_HEIGHT - i - 1) * GEM_H,
				getNextGemID()
			);
			newColumn.push_back(newGem);
		}
		boardGems_.push_back(newColumn);
	}
	//Move all gems to the left
	x_ -= GEM_W * n;
	for (std::vector<Gem*> column : boardGems_) {
		for (Gem* gem : column) {
			gem->Move(-GEM_W * n, 0);
		}
	}
	columnTimer_->ResetTimer(GameManager::Instance()->timePerColumn());
	
	if (x_ < ENDLINE_X)
		gameLost_ = true;
}

void Board::fillBoard() {
	if (GameManager::Instance()->fillsLeft() > 0) {
		int maxGapHeight = 0;
		std::vector<Gem*> createdGems;

		//Creates gems in their correct places
		for (int i = 0; i < boardGems_.size(); i++) {
			std::vector<Gem*>& column = boardGems_.at(i);

			int thisGapHeight = 0;

			while (column.size() < 10) {

				++thisGapHeight;
				maxGapHeight = std::max(maxGapHeight, thisGapHeight);

				std::uniform_int_distribution<int> distribution(0, GEM_TYPE_NUMBER - 1);

				Gem::GemColor color = Gem::GemColor(distribution(generator_));

				Gem* newGem = new Gem(
					color,
					x_ + i * GEM_W,
					y_ + (BOARD_HEIGHT - (float)column.size() - 1) * GEM_H,
					getNextGemID()
				);

				createdGems.push_back(newGem);
				column.push_back(newGem);
			}
		}
		//Vertical offset just enough so they fall from the top
		for (Gem* gem : createdGems) {
			gem->setY(gem->y() - maxGapHeight * GEM_H);
			gem->Move(0, maxGapHeight * GEM_H);
		}
		if (createdGems.size() > 0)
			GameManager::Instance()->useFill();
	}
}

void Board::searchGemGroup(int gX, int gY) {

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
				if (this_gem->gemColor() != gemColor || 
					std::find(toDelete.begin(), toDelete.end(), this_gem->id()) != toDelete.end()) {
					return 0;
				}
				//Else add gem to delete.
				else {
					toDelete.push_back(this_gem->id());
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

	gemNumber = recursion(dir::NONE, boardGems_.at(gX).at(gY)->gemColor(), gX, gY);

	if (gemNumber > 1) {
		for (int i = boardGems_.size() - 1; i >= 0; --i) {
			for (int ii = boardGems_.at(i).size() - 1; ii >= 0; --ii) {
				if (std::find(toDelete.begin(), toDelete.end(), boardGems_.at(i).at(ii)->id()) != toDelete.end()) {
					eraseGem(i, ii);
				}
			}
		}
		//Update Score
		GameManager::Instance()->AddScore(gemNumber);
	}
}

void Board::eraseGem(int gX, int gY) {
	std::vector<Gem*>& column = boardGems_.at(gX);
	
	beingDestroyedGems_.push_back(column.at(gY));
	column.at(gY)->TransitState(Gem::GemState::BREAKING);
	column.erase(column.begin() + gY);

	//Update position for every Gem above
	for (int i = gY; i < column.size(); ++i) {
		column.at(i)->Move(0, GEM_H);
	}

	//Check if column empty
	if (column.empty()) {
		boardGems_.erase(boardGems_.begin() + gX);

		//Move Board Origin
		x_ += GEM_W;

		//Move all left-hand gems.
		for (int i = 0; i < gX; ++i) {
			for (Gem* gem : boardGems_.at(i)) {
				gem->Move(GEM_W, 0);
			}
		}
	}
}