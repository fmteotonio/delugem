#include "Board.h"

#include "../InputHandler.h"
#include "../TextureManager.h"

#include <cmath>
#include <chrono>
#include <algorithm>
#include <functional>
#include <iterator>

Board::Board(float x, float y) {

	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(SPR_BOARD_AUX);
	GameObject::Init(x, y, BOARD_AUX_W, BOARD_AUX_H, objTexture, new Animation("Still", 0, 0));
	
	generator_.seed(std::chrono::system_clock::now().time_since_epoch().count());

	for (int i = 0; i < 20; ++i) {
		makeNewColumn();
	}
}


void Board::Update(int deltaTime) {

	moveBoard((float)scrollSpeed_ * deltaTime/1000.0f);

	HandleInput();

	for (std::vector<Gem*> column : boardGems_) {
		for (Gem* gem : column) {
			gem->Update(deltaTime);
		}
	}
	for (size_t i = 0; i < beingDestroyedGems_.size(); ++i) {
		if (beingDestroyedGems_.at(i)->gemStatus() == Gem::GemStatus::TO_DESTROY) {
			delete beingDestroyedGems_.at(i);
			beingDestroyedGems_.erase(beingDestroyedGems_.begin() + i);
		}
	}
}

void Board::HandleInput() {
	if (InputHandler::Instance()->mouseLeft() && !hasClicked_) {
		hasClicked_ = true;
		clickPiece(InputHandler::Instance()->mouseX(), InputHandler::Instance()->mouseY());
	}
	else if (!InputHandler::Instance()->mouseLeft() && hasClicked_)
		hasClicked_ = false;
}

void Board::Render() {

	GameObject::Render();
	
	for (std::vector<Gem*> column : boardGems_) {
		for (Gem* gem : column) {
			gem->Render();
		}
	}
	for (Gem* gem : beingDestroyedGems_) {
		gem->Render();
	}
}

int Board::getNextGemID() {
	return ++nextGemID_;
}

void Board::makeNewColumn() {

	std::uniform_int_distribution<int> distribution(0,GEM_TYPE_NUMBER-1);
	
	std::vector<Gem*> newColumn;
	for (int i = 0; i < 10; ++i) {

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

void Board::clickPiece(Sint32 mouseX, Sint32 mouseY) {

	int conv_x = int(floor((mouseX/GAME_SCALE - x_) / GEM_W));
	int conv_y = int(floor(BOARD_HEIGHT - (mouseY/GAME_SCALE - y_) / GEM_H));

	if (conv_x >= 0 && conv_x < boardGems_.size()) {
		if (conv_y >= 0 && conv_y < boardGems_.at(conv_x).size()) {
			searchGemGroup(conv_x, conv_y);
		}
	}
}

void Board::moveBoard(float x) {
	x_ += x;
	for (std::vector<Gem*> column : boardGems_) {
		for (Gem* gem : column) {
			gem->Move(x, 0);
		}
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
	}
}

void Board::eraseGem(int gX, int gY) {
	std::vector<Gem*>& column = boardGems_.at(gX);
	
	beingDestroyedGems_.push_back(column.at(gY));
	column.at(gY)->DestroyGem();
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