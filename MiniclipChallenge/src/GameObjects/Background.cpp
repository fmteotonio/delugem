#include "Background.h"

#include "../TextureManager.h"
#include "../Constants.h"

#include <iostream>

const char* Background::cPath		 =  "res/images/background.png";
const int   Background::cMaxSteps	 =	15;
const int   Background::cTimePerStep =	60;
const int   Background::cW			 =	SCREEN_W + cMaxSteps;
const int   Background::cH			 =	SCREEN_H;

Background::Background(Position pos) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);

	stepTimer_ = new Timer(cTimePerStep, true);

	AddAnimation("Default", new Animation(0, 0));
	AnimatedGameObject::Init(pos, cW, cH, objTexture, "Default", true);
}

void Background::Update(int deltaTime) {
	AnimatedGameObject::Update(deltaTime);
	stepTimer_->Update(deltaTime);
	if (stepTimer_->HasRung()) {
		if (steps_ < cMaxSteps) {
			++steps_;
			pos_.x += 1;
		}
		else {
			steps_ = 0;
			pos_.x -= cMaxSteps;
		}
		stepTimer_->ResetTimer();
	}
}