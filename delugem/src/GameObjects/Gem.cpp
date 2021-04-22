#include "Gem.h"

#include "../TextureManager.h"

#include <cmath>
#include <iostream>

const char*      Gem::cPath           = "res/images/gems.png";
const Dimensions Gem::cDim            = { 16, 16 };
const float      Gem::cAcceleration   = 0.45f / 1000; //increase speed by 0.45 pixels per s.
const int	     Gem::cNumberOfColors = 5;

const char*		 Gem::cAnimDefault   = "Default";
const char*		 Gem::cAnimHovered   = "Hovered";
const char*		 Gem::cAnimBreaking  = "Breaking";
const char*		 Gem::cAnimToDestroy = "ToDestroy";

Gem::Gem(Position pos, GemColor gemColor, int id) {
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
		default: 
			frameRow = 0;
			std::cerr << "GemColor not valid." << std::endl;
	}

	AddAnimation(cAnimDefault,   new Animation(0, frameRow));
	AddAnimation(cAnimHovered,   new Animation(6, frameRow));
	AddAnimation(cAnimBreaking,  new Animation(0, 5, frameRow, 40));
	AddAnimation(cAnimToDestroy, new Animation(5, frameRow));

	AnimatedGameObject::Init(pos, cDim, objTexture, cAnimDefault, false);
}

int Gem::GetId() { 
	return _id; 
}

Gem::GemColor Gem::GetGemColor()   { 
	return _gemColor; 
}

Gem::GemState Gem::GetGemState() { 
	return _gemState; 
}

/* Returns true if Gem is moving on the axis indicated in the arguments */
bool Gem::isMoving(bool onXAxis, bool onYAxis) {
	return (onXAxis && _toMove.x != 0) || (onYAxis && _toMove.y != 0);
}

/* Sets movement target to pos + deltaPos */
void Gem::MoveTo(Position deltaPos) {
	_toMove.x += deltaPos.x;
	_toMove.y += deltaPos.y;
}

/* Moves gem instantly to pos + deltaPos, and sets move target to original position */
void Gem::MoveFrom(Position deltaPos) {
	_pos.x += deltaPos.x;
	_pos.y += deltaPos.y;
	MoveTo({ -deltaPos.x, -deltaPos.y });
}

bool Gem::TransitState(GemState newGemState) {
	switch (newGemState) {
		case GemState::DEFAULT: {
			if (_gemState == GemState::HOVERED) {
				_gemState = newGemState;
				SetAnimation(cAnimDefault, false);
				return true;
			}
			break;
		}
		case GemState::HOVERED: {
			if (_gemState == GemState::DEFAULT) {
				_gemState = newGemState;
				SetAnimation(cAnimHovered, false);
				return true;
			}
			break;
		}
		case GemState::BREAKING: {
			if (_gemState == GemState::DEFAULT || _gemState == GemState::HOVERED) {
				_gemState = newGemState;
				SetAnimation(cAnimBreaking, true);
				return true;
			}
			break;
		}
		case GemState::TO_DESTROY: {
			_gemState = newGemState;
			SetAnimation(cAnimToDestroy, false);
			return true;
		}
	}
	std::cerr << "Illegal GemState Transition from " << int(_gemState) << " to " << int(newGemState) << "\n";
	return false;
}

void Gem::Update(int deltaTime) {

	//Calculate amount to move in this frame.
	Position moveUnit = { _v.x * deltaTime ,  _v.y * deltaTime };

	if (_toMove.x != 0) {
		if (abs(_toMove.x) < abs(moveUnit.x)) {
			_pos.x += _toMove.x;
			_toMove.x = 0;
			_v.x = 0;
		}
		else {
			_pos.x += moveUnit.x;
			_toMove.x -= moveUnit.x;
			_v.x += copysign(cAcceleration, _toMove.x) * deltaTime;
		}
	}
	if (_toMove.y != 0) {
		if (abs(_toMove.y) < abs(moveUnit.y)) {
			_pos.y += _toMove.y;
			_toMove.y = 0;
			_v.y = 0;
		}
		else {
			_pos.y += moveUnit.y;
			_toMove.y -= moveUnit.y;
			_v.y += copysign(cAcceleration, _toMove.y) * deltaTime;
		}
	}

	//Check if gem should be destroyed
	if (_currentAnimation->HasPlayedOnce() && _gemState == GemState::BREAKING) {
		TransitState(GemState::TO_DESTROY);
	}

	AnimatedGameObject::Update(deltaTime);
}