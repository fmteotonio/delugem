#include "Background.h"

#include "../TextureManager.h"
#include "../Constants.h"

#include <iostream>

const char* Background::cPath_ =        "res/images/background.png";
const int   Background::cMaxSteps_ =	15;
const int   Background::cTimePerStep_ =	60;
const int   Background::cW =			SCREEN_W + cMaxSteps_;
const int   Background::cH =			SCREEN_H;

Background::Background(float x, float y) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath_);

	stepTimer_ = new Timer(cTimePerStep_, true);

	AddAnimation("Default", new Animation(0, 0));
	AnimatedGameObject::Init(x, y, cW, cH, objTexture, "Default", true);
}

void Background::Update(int deltaTime) {
	AnimatedGameObject::Update(deltaTime);
	stepTimer_->Update(deltaTime);
	if (stepTimer_->HasRung()) {
		if (steps_ < cMaxSteps_) {
			++steps_;
			x_ += 1;
		}
		else {
			steps_ = 0;
			x_ -= cMaxSteps_;
		}
		stepTimer_->ResetTimer();
	}
}