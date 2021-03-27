#include "ForegroundStrip.h"

#include "../TextureManager.h"
#include "../Constants.h"

#include <iostream>

const char* ForegroundStrip::cPath =    "res/images/foregroundstrip.png";
const int   ForegroundStrip::cW =       SCREEN_W;
const int   ForegroundStrip::cH =       28;
const int   ForegroundStrip::cSourceW = 1;

ForegroundStrip::ForegroundStrip(float x, float y) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);

	AddAnimation("Default", new Animation(0, 0));
	AddAnimation("LevelUp", new Animation(0, 16, 0, 30));

	AnimatedGameObject::Init(x, y, cW, cH, objTexture, "Default", false);
}

void ForegroundStrip::Update(int deltaTime) {
	AnimatedGameObject::Update(deltaTime);

	if (currentAnimation_->HasPlayedOnce() && foregroundStripState_ == ForegroundStripState::LEVELUP) {
		TransitState(ForegroundStripState::DEFAULT);
	}
}

void ForegroundStrip::Render() {
	SDL_Rect src;
	src.x = currentAnimation_->GetCurrentFrame() * cSourceW;
	src.y = currentAnimation_->GetFrameRow() * h_;
	src.w = cSourceW;
	src.h = h_;

	SDL_Rect dest;
	//Convert to Int before Scale to avoid sub-pixel movement
	dest.x = static_cast<int>(round(x_)) * GAME_SCALE;
	dest.y = static_cast<int>(round(y_)) * GAME_SCALE;
	dest.w = w_ * GAME_SCALE;
	dest.h = h_ * GAME_SCALE;
	TextureManager::Instance()->Draw(texture_, src, dest);
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
	std::cerr << "Illegal ForegroundStripState Transition from " << int(foregroundStripState_) << " to " << int(newForegroundStripState) << "\n";
	return false;
}