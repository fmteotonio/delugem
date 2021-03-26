#include "ForegroundStrip.h"

#include "../TextureManager.h"

#include <iostream>

const char* ForegroundStrip::cPath = "res/images/foregroundstrip.png";
const int   ForegroundStrip::cW =    SCREEN_W;
const int   ForegroundStrip::cH =    28;

ForegroundStrip::ForegroundStrip(float x, float y) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);

	AddAnimation("Default", new Animation(0, 0));
	AddAnimation("LevelUp", new Animation(0, 8, 0, 80));

	AnimatedGameObject::Init(x, y, cW, cH, objTexture, "Default", false);
}

void ForegroundStrip::Update(int deltaTime) {
	AnimatedGameObject::Update(deltaTime);

	if (currentAnimation_->HasPlayedOnce() && foregroundStripState_ == ForegroundStripState::LEVELUP) {
		TransitState(ForegroundStripState::DEFAULT);
	}
}

bool ForegroundStrip::TransitState(ForegroundStripState newForegroundStripState) {
	switch (newForegroundStripState) {
		case ForegroundStripState::DEFAULT: {
			if (foregroundStripState_ == ForegroundStripState::LEVELUP) {
				foregroundStripState_ = newForegroundStripState;
				SetAnimation("Default", false);
				return true;
			}
			break;
		}
		case ForegroundStripState::LEVELUP: {
			if (foregroundStripState_ == ForegroundStripState::DEFAULT) {
				foregroundStripState_ = newForegroundStripState;
				SetAnimation("LevelUp", true);
				return true;
			}
			break;
		}
	}
	std::cout << "Illegal ForegroundStripState Transition from " << int(foregroundStripState_) << " to " << int(newForegroundStripState) << "\n";
	return false;
}