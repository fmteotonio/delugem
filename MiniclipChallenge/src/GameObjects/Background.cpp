#include "Background.h"

#include "../TextureManager.h"
#include "../Constants.h"

#include <iostream>

const char* Background::cPath		 =  "res/images/background.png";
const int   Background::cMaxSteps	 =	15;
const int   Background::cTimePerStep =	60;
const Dimensions Background::cDim    = { SCREEN_W + cMaxSteps , SCREEN_H };

Background::Background(Position pos) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);

	_stepTimer = new Timer(cTimePerStep, true);

	AddAnimation("Default", new Animation(0, 0));
	AnimatedGameObject::Init(pos, cDim, objTexture, "Default", true);
}

void Background::Update(int deltaTime) {
	AnimatedGameObject::Update(deltaTime);
	_stepTimer->Update(deltaTime);
	if (_stepTimer->HasRung()) {
		if (_steps < cMaxSteps) {
			++_steps;
			_pos.x += 1;
		}
		else {
			_steps = 0;
			_pos.x -= cMaxSteps;
		}
		_stepTimer->ResetTimer();
	}
}