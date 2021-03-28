#include "ForegroundStrip.h"

#include "../TextureManager.h"
#include "../Constants.h"

#include <iostream>

const char* ForegroundStrip::cPath =    "res/images/foregroundstrip.png";
const int   ForegroundStrip::cSourceW = 1;

const Dimensions ForegroundStrip::cDim = { SCREEN_W, 28 };

ForegroundStrip::ForegroundStrip(Position pos) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);

	AddAnimation("Default", new Animation(0, 0));
	AddAnimation("LevelUp", new Animation(0, 16, 0, 30));

	AnimatedGameObject::Init(pos, cDim, objTexture, "Default", false);
}

void ForegroundStrip::Update(int deltaTime) {
	AnimatedGameObject::Update(deltaTime);

	if (_currentAnimation->HasPlayedOnce() && _foregroundStripState == ForegroundStripState::LEVELUP) {
		TransitState(ForegroundStripState::DEFAULT);
	}
}

void ForegroundStrip::Render() {
	SDL_Rect src;
	src.x = _currentAnimation->GetCurrentFrame() * cSourceW;
	src.y = _currentAnimation->GetFrameRow() * _dim.h;
	src.w = cSourceW;
	src.h = _dim.h;

	SDL_Rect dest;
	//Convert to Int before Scale to avoid sub-pixel movement
	dest.x = static_cast<int>(round(_pos.x)) * GAME_SCALE;
	dest.y = static_cast<int>(round(_pos.y)) * GAME_SCALE;
	dest.w = _dim.w * GAME_SCALE;
	dest.h = _dim.h * GAME_SCALE;
	TextureManager::Instance()->Draw(_texture, src, dest);
}

bool ForegroundStrip::TransitState(ForegroundStripState newForegroundStripState) {
	switch (newForegroundStripState) {
		case ForegroundStripState::DEFAULT: {
			if (_foregroundStripState == ForegroundStripState::LEVELUP) {
				_foregroundStripState = newForegroundStripState;
				SetAnimation("Default", false);
				return true;
			}
			break;
		}
		case ForegroundStripState::LEVELUP: {
			if (_foregroundStripState == ForegroundStripState::DEFAULT) {
				_foregroundStripState = newForegroundStripState;
				SetAnimation("LevelUp", true);
				return true;
			}
			break;
		}
	}
	std::cerr << "Illegal ForegroundStripState Transition from " << int(_foregroundStripState) << " to " << int(newForegroundStripState) << "\n";
	return false;
}