#include "Gem.h"

#include "../TextureManager.h"
#include "../Constants.h"

#include <cmath>
#include <iostream>

const char* Gem::cPath = "res/images/gems.png";

const Dimensions Gem::cDim = { 16, 16 };

const int   Gem::cAcceleration = 450;
const int	Gem::cNumberOfColors = 5;

Gem::Gem(GemColor gemColor, Position pos, int id) {
	_gemColor = gemColor;
	_id = id;

	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);
	
	int frameRow;
	switch (_gemColor) {
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

	AnimatedGameObject::Init(pos, cDim, objTexture, "Default", false);
}

int Gem::GetId() { return _id; }
Gem::GemColor Gem::GetGemColor()   { return _gemColor; }
Gem::GemState Gem::GetGemState() { return _gemState; }

void Gem::Move(float x, float y) {
	_toMoveX += x;
	_toMoveY += y;
}

void Gem::MoveFrom(float deltaX, float deltaY) {
	_pos.x += deltaX;
	_pos.y += deltaY;
	Move(-deltaX, -deltaY);
}

bool Gem::isMoving() {
	return _toMoveX != 0 || _toMoveY != 0;
}

void Gem::Update(int deltaTime) {
	//Amount to move in this frame.
	float moveUnitX = _vx * (deltaTime / 1000.0f);
	float moveUnitY = _vy * (deltaTime / 1000.0f);
	if (_toMoveX != 0) {
		if (abs(_toMoveX) < abs(moveUnitX)) {
			_pos.x += _toMoveX;
			_toMoveX -= _toMoveX;
			_vx = 0;
		}
		else {
			_pos.x += moveUnitX;
			_toMoveX -= moveUnitX;
			_vx += copysign(cAcceleration, _toMoveX) * (deltaTime / 1000.0f);
		}
	}
	if (_toMoveY != 0) {
		if (abs(_toMoveY) < abs(moveUnitY)) {
			_pos.y += _toMoveY;
			_toMoveY -= _toMoveY;
			_vy = 0;
		}
		else {
			_pos.y += moveUnitY;
			_toMoveY -= moveUnitY;
			_vy += copysign(cAcceleration, _toMoveY) * (deltaTime / 1000.0f);
		}
	}

	if (_currentAnimation->HasPlayedOnce() && _gemState == GemState::BREAKING) {
		TransitState(GemState::TO_DESTROY);
	}
	AnimatedGameObject::Update(deltaTime);
}

bool Gem::TransitState(GemState newGemState) {
	switch (newGemState) {
		case GemState::DEFAULT: {
			if (_gemState == GemState::HOVERED) {
				_gemState = newGemState;
				SetAnimation("Default", false);
				return true;
			}
			break;
		}
		case GemState::HOVERED: {
			if (_gemState == GemState::DEFAULT) {
				_gemState = newGemState;
				SetAnimation("Hovered", false);
				return true;
			}
			break;
		}
		case GemState::BREAKING: {
			if (_gemState == GemState::DEFAULT || _gemState == GemState::HOVERED) {
				_gemState = newGemState;
				SetAnimation("Breaking", true);
				return true;
			}
			break;
		}
		case GemState::TO_DESTROY: {
			_gemState = newGemState;
			SetAnimation("ToDestroy", false);
			return true;
		}
	}
	std::cerr << "Illegal GemState Transition from " << int(_gemState) << " to " << int(newGemState) << "\n";
	return false;
}