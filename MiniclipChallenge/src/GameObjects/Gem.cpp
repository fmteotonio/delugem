#include "Gem.h"

#include "../TextureManager.h"
#include "../Constants.h"

#include <cmath>
#include <iostream>

Gem::Gem(GemColor gemColor, float x, float y, int id) {
	gemColor_ = gemColor;
	id_ = id;

	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(SPR_GEMS);
	
	int frameRow;
	switch (gemColor_) {
		case(GemColor::BEIGE):  frameRow = 0; break;
		case(GemColor::BLUE):   frameRow = 1; break;
		case(GemColor::GREEN):  frameRow = 2; break;
		case(GemColor::ORANGE): frameRow = 3; break;
		case(GemColor::PINK):   frameRow = 4; break;
		default: frameRow = 0;
	}

	//ANIMATION
	defaultAnimation_ =	  new Animation(0, frameRow);
	hoveredAnimation_ =   new Animation(6, frameRow);
	breakingAnimation_ =  new Animation(0, 5, frameRow, 40);
	toDestroyAnimation_ = new Animation(5, frameRow);

	GameObject::Init(x, y, GEM_W, GEM_H, objTexture, defaultAnimation_);
}

int Gem::id() { return id_; }
Gem::GemColor Gem::gemColor()   { return gemColor_; }
Gem::GemState Gem::gemState() { return gemState_; }

void Gem::Move(float x, float y) {
	toMoveX_ += x;
	toMoveY_ += y;
}
bool Gem::isMoving() {
	return toMoveX_ != 0 || toMoveY_ != 0;
}

void Gem::Update(int deltaTime) {
	//Amount to move in this frame.
	float moveUnitX = vx_ * (deltaTime / 1000.0f);
	float moveUnitY = vy_ * (deltaTime / 1000.0f);
	if (toMoveX_ != 0) {
		if (abs(toMoveX_) < abs(moveUnitX)) {
			x_ += toMoveX_;
			toMoveX_ -= toMoveX_;
			vx_ = 0;
		}
		else {
			x_ += moveUnitX;
			toMoveX_ -= moveUnitX;
			vx_ += copysign(a_, toMoveX_) * (deltaTime / 1000.0f);
		}
	}
	if (toMoveY_ != 0) {
		if (abs(toMoveY_) < abs(moveUnitY)) {
			y_ += toMoveY_;
			toMoveY_ -= toMoveY_;
			vy_ = 0;
		}
		else {
			y_ += moveUnitY;
			toMoveY_ -= moveUnitY;
			vy_ += copysign(a_, toMoveY_) * (deltaTime / 1000.0f);
		}
	}

	if (animation_->PlayedOnce() && gemState_ == GemState::BREAKING) {
		TransitState(GemState::TO_DESTROY);
	}
	GameObject::Update(deltaTime);
}

void Gem::Render() {
	GameObject::Render();
}

void Gem::Clean() {
	delete defaultAnimation_;
	delete hoveredAnimation_;
	delete breakingAnimation_;
	delete toDestroyAnimation_;
}

bool Gem::TransitState(GemState newGemState) {
	switch (newGemState) {
		case GemState::DEFAULT: {
			if (gemState_ == GemState::HOVERED) {
				gemState_ = newGemState;
				animation_ = defaultAnimation_;
				return true;
			}
			break;
		}
		case GemState::HOVERED: {
			if (gemState_ == GemState::DEFAULT) {
				gemState_ = newGemState;
				animation_ = hoveredAnimation_;
				return true;
			}
			break;
		}
		case GemState::BREAKING: {
			if (gemState_ == GemState::DEFAULT || gemState_ == GemState::HOVERED) {
				gemState_ = newGemState;
				animation_ = breakingAnimation_;
				animation_->Play();
				return true;
			}
			break;
		}
		case GemState::TO_DESTROY: {
			gemState_ = newGemState;
			animation_ = toDestroyAnimation_;
			return true;
		}
	}
	std::cout << "Illegal GemState Transition from " << int(gemState_) << " to " << int(newGemState) << "\n";
	return false;
}