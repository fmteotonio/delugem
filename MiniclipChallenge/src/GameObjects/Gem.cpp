#include "Gem.h"

#include "../TextureManager.h"
#include "../Constants.h"

#include <cmath>
#include <iostream>

const char* Gem::cPath = "res/images/gems.png";
const int   Gem::cW = 16;
const int   Gem::cH = 16;
const int   Gem::cAcceleration = 450;
const int	Gem::cNumberOfColors = 5;

Gem::Gem(GemColor gemColor, float x, float y, int id) {
	gemColor_ = gemColor;
	id_ = id;

	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);
	
	int frameRow;
	switch (gemColor_) {
		case(GemColor::BEIGE):  frameRow = 0; break;
		case(GemColor::BLUE):   frameRow = 1; break;
		case(GemColor::GREEN):  frameRow = 2; break;
		case(GemColor::ORANGE): frameRow = 3; break;
		case(GemColor::PINK):   frameRow = 4; break;
		default: frameRow = 0;
	}

	AddAnimation("Default", new Animation(0, frameRow));
	AddAnimation("Hovered", new Animation(6, frameRow));
	AddAnimation("Breaking", new Animation(0, 5, frameRow, 40));
	AddAnimation("ToDestroy", new Animation(5, frameRow));

	AnimatedGameObject::Init(x, y, cW, cH, objTexture, "Default", false);
}

int Gem::GetId() { return id_; }
Gem::GemColor Gem::GetGemColor()   { return gemColor_; }
Gem::GemState Gem::GetGemState() { return gemState_; }

void Gem::SetY(float y) {
	y_ = y;
}

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
			vx_ += copysign(cAcceleration, toMoveX_) * (deltaTime / 1000.0f);
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
			vy_ += copysign(cAcceleration, toMoveY_) * (deltaTime / 1000.0f);
		}
	}

	if (currentAnimation_->HasPlayedOnce() && gemState_ == GemState::BREAKING) {
		TransitState(GemState::TO_DESTROY);
	}
	AnimatedGameObject::Update(deltaTime);
}

bool Gem::TransitState(GemState newGemState) {
	switch (newGemState) {
		case GemState::DEFAULT: {
			if (gemState_ == GemState::HOVERED) {
				gemState_ = newGemState;
				SetAnimation("Default", false);
				return true;
			}
			break;
		}
		case GemState::HOVERED: {
			if (gemState_ == GemState::DEFAULT) {
				gemState_ = newGemState;
				SetAnimation("Hovered", false);
				return true;
			}
			break;
		}
		case GemState::BREAKING: {
			if (gemState_ == GemState::DEFAULT || gemState_ == GemState::HOVERED) {
				gemState_ = newGemState;
				SetAnimation("Breaking", true);
				return true;
			}
			break;
		}
		case GemState::TO_DESTROY: {
			gemState_ = newGemState;
			SetAnimation("ToDestroy", false);
			return true;
		}
	}
	std::cerr << "Illegal GemState Transition from " << int(gemState_) << " to " << int(newGemState) << "\n";
	return false;
}