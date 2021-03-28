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

void Gem::Move(Position pos) {
	_toMove.x += pos.x;
	_toMove.y += pos.y;
}

void Gem::MoveFrom(Position deltaPos) {
	_pos.x += deltaPos.x;
	_pos.y += deltaPos.y;
	Move({ -deltaPos.x, -deltaPos.y });
}

bool Gem::isMoving(bool onXAxis, bool onYAxis) {
	return (onXAxis && _toMove.x != 0) || (onYAxis && _toMove.y != 0);
}

void Gem::Update(int deltaTime) {
	//Amount to move in this frame.
	Position moveUnit = { _v.x * (deltaTime / 1000.0f) ,  _v.y * (deltaTime / 1000.0f) };

	if (_toMove.x != 0) {
		if (abs(_toMove.x) < abs(moveUnit.x)) {
			_pos.x += _toMove.x;
			_toMove.x -= _toMove.x;
			_v.x = 0;
		}
		else {
			_pos.x += moveUnit.x;
			_toMove.x -= moveUnit.x;
			_v.x += copysign(cAcceleration, _toMove.x) * (deltaTime / 1000.0f);
		}
	}
	if (_toMove.y != 0) {
		if (abs(_toMove.y) < abs(moveUnit.y)) {
			_pos.y += _toMove.y;
			_toMove.y -= _toMove.y;
			_v.y = 0;
		}
		else {
			_pos.y += moveUnit.y;
			_toMove.y -= moveUnit.y;
			_v.y += copysign(cAcceleration, _toMove.y) * (deltaTime / 1000.0f);
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