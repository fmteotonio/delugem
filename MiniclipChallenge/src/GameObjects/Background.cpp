#include "Background.h"

#include "../TextureManager.h"
#include "../Constants.h"

#include <iostream>

const char* Background::cPath		 =  "res/images/background.png";
const int   Background::cMaxSteps	 =	15;
const int   Background::cTimePerStep =	60;
const int   Background::cW			 =	SCREEN_W + cMaxSteps;
const int   Background::cH			 =	SCREEN_H;

Background::Background(float x, float y) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);

	stepTimer_ = new Timer(cTimePerStep, true);

	AddAnimation("Default", new Animation(0, 0));
	AnimatedGameObject::Init(x, y, cW, cH, objTexture, "Default", true);
}

void Background::Update(int deltaTime) {
	AnimatedGameObject::Update(deltaTime);
	stepTimer_->Update(deltaTime);
	if (stepTimer_->HasRung()) {
		if (steps_ < cMaxSteps) {
			++steps_;
			x_ += 1;
		}
		else {
			steps_ = 0;
			x_ -= cMaxSteps;
		}
		stepTimer_->ResetTimer();
	}
}