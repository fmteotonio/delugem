#include "Background.h"

#include "../TextureManager.h"
#include "../Constants.h"

const char* Background::cPath		 =  "res/images/background.png";
const int   Background::cMaxSteps	 =	15;
const int   Background::cTimePerStep =	60;
const Dimensions Background::cDim    = { SCREEN_W + cMaxSteps , SCREEN_H };

const char* Background::cAnimDefault = "Default";

Background::Background(Position pos) {
	_stepTimer = new Timer(cTimePerStep, true);

	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);

	AddAnimation(cAnimDefault, new Animation(0, 0));

	AnimatedGameObject::Init(pos, cDim, objTexture, cAnimDefault, true);
}

void Background::Update(int deltaTime) {
	AnimatedGameObject::Update(deltaTime);
	_stepTimer->Update(deltaTime);

	if (_stepTimer->HasEnded()) {
		if (_steps < cMaxSteps) {
			++_steps;
			++_pos.x;
		}
		else {
			_steps = 0;
			_pos.x -= cMaxSteps;
		}
		_stepTimer->ResetTimer();
	}
}

void Background::Clean() {
	AnimatedGameObject::Clean();
	delete _stepTimer;
}