#include "ForegroundStrip.h"

#include "../TextureManager.h"
#include "../Constants.h"

#include <iostream>

const char*      ForegroundStrip::cPath	   = "res/images/foregroundstrip.png";
const Dimensions ForegroundStrip::cSrcDim  = {        1, 28 };
const Dimensions ForegroundStrip::cDestDim = { SCREEN_W, 28 };

const char* ForegroundStrip::cAnimDefault = "Default";
const char* ForegroundStrip::cAnimLevelUp = "LevelUp";

ForegroundStrip::ForegroundStrip(Position pos) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);

	AddAnimation(cAnimDefault, new Animation(0, 0));
	AddAnimation(cAnimLevelUp, new Animation(0, 16, 0, 30));

	AnimatedGameObject::Init(pos, cSrcDim, cDestDim,  objTexture, cAnimDefault, false);
}

void ForegroundStrip::Update(int deltaTime) {
	AnimatedGameObject::Update(deltaTime);

	if (_foregroundStripState == ForegroundStripState::LEVELUP && _currentAnimation->HasPlayedOnce()) {
		TransitState(ForegroundStripState::DEFAULT);
	}
}

bool ForegroundStrip::TransitState(ForegroundStripState newForegroundStripState) {
	switch (newForegroundStripState) {
		case ForegroundStripState::DEFAULT: {
			if (_foregroundStripState == ForegroundStripState::LEVELUP) {
				_foregroundStripState = newForegroundStripState;
				SetAnimation(cAnimDefault, false);
				return true;
			}
			break;
		}
		case ForegroundStripState::LEVELUP: {
			if (_foregroundStripState == ForegroundStripState::DEFAULT) {
				_foregroundStripState = newForegroundStripState;
				SetAnimation(cAnimLevelUp, true);
				return true;
			}
			break;
		}
	}
	std::cerr << "Illegal ForegroundStripState Transition from " << int(_foregroundStripState) << " to " << int(newForegroundStripState) << "\n";
	return false;
}