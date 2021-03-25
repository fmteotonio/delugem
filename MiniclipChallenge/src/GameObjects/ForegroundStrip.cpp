#include "ForegroundStrip.h"

#include "../Constants.h"
#include "../TextureManager.h"

#include <iostream>

ForegroundStrip::ForegroundStrip(float x, float y) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(SPR_FOREGROUNDSTRIP);
	defaultAnimation_ = new Animation(0, 0);
	levelUpAnimation_ = new Animation(0, 8, 0, 80);
	GameObject::Init(x, y, FOREGROUNDSTRIP_W, FOREGROUNDSTRIP_H, objTexture, defaultAnimation_);
}

void ForegroundStrip::Render() {
	GameObject::Render();
}

void ForegroundStrip::Update(int deltaTime) {
	GameObject::Update(deltaTime);

	if (animation_->PlayedOnce() && foregroundStripState_ == ForegroundStripState::LEVELUP) {
		TransitState(ForegroundStripState::DEFAULT);
	}
}

void ForegroundStrip::Clean() {
	delete defaultAnimation_;
	delete levelUpAnimation_;
}

bool ForegroundStrip::TransitState(ForegroundStripState newForegroundStripState) {
	switch (newForegroundStripState) {
		case ForegroundStripState::DEFAULT: {
			if (foregroundStripState_ == ForegroundStripState::LEVELUP) {
				foregroundStripState_ = newForegroundStripState;
				animation_ = defaultAnimation_;
				return true;
			}
			break;
		}
		case ForegroundStripState::LEVELUP: {
			if (foregroundStripState_ == ForegroundStripState::DEFAULT) {
				foregroundStripState_ = newForegroundStripState;
				animation_ = levelUpAnimation_;
				animation_->Play();
				return true;
			}
			break;
		}
	}
	std::cout << "Illegal ForegroundStripState Transition from " << int(foregroundStripState_) << " to " << int(newForegroundStripState) << "\n";
	return false;
}