#include "ForegroundStrip.h"

#include "../Constants.h"
#include "../TextureManager.h"

#include <iostream>

ForegroundStrip::ForegroundStrip(float x, float y) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(SPR_FOREGROUNDSTRIP);

	addAnimation("Default", new Animation(0, 0));
	addAnimation("LevelUp", new Animation(0, 8, 0, 80));

	AnimatedGameObject::Init(x, y, FOREGROUNDSTRIP_W, FOREGROUNDSTRIP_H, objTexture, "Default", false);
}

void ForegroundStrip::Render() {
	AnimatedGameObject::Render();
}

void ForegroundStrip::Update(int deltaTime) {
	AnimatedGameObject::Update(deltaTime);

	if (currentAnimation_->PlayedOnce() && foregroundStripState_ == ForegroundStripState::LEVELUP) {
		TransitState(ForegroundStripState::DEFAULT);
	}
}

void ForegroundStrip::Clean() {
	//GameObject just cleans animationvector;
}

bool ForegroundStrip::TransitState(ForegroundStripState newForegroundStripState) {
	switch (newForegroundStripState) {
		case ForegroundStripState::DEFAULT: {
			if (foregroundStripState_ == ForegroundStripState::LEVELUP) {
				foregroundStripState_ = newForegroundStripState;
				setAnimation("Default", false);
				return true;
			}
			break;
		}
		case ForegroundStripState::LEVELUP: {
			if (foregroundStripState_ == ForegroundStripState::DEFAULT) {
				foregroundStripState_ = newForegroundStripState;
				setAnimation("LevelUp", true);
				return true;
			}
			break;
		}
	}
	std::cout << "Illegal ForegroundStripState Transition from " << int(foregroundStripState_) << " to " << int(newForegroundStripState) << "\n";
	return false;
}