#include "Background.h"

#include "../TextureManager.h"
#include "../Constants.h"

const char* Background::cPath		 =  "res/images/background.png";
const int   Background::cMaxSteps	 =	15;
const int   Background::cTimePerStep =	60;
const Dimensions Background::cDim    = { SCREEN_W + cMaxSteps , SCREEN_H };

const char* Background::cAnimDefault = "Default";

int Background::_steps = 0;
Timer Background::_stepTimer = Timer(cTimePerStep, true);

Background::Background() {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);

	AddAnimation(cAnimDefault, new Animation(0, 0));

	Position pos = { -cMaxSteps + _steps , 0 };

	AnimatedGameObject::Init(pos, cDim, objTexture, cAnimDefault, true);
}

void Background::Update(int deltaTime) {
	AnimatedGameObject::Update(deltaTime);
	_stepTimer.Update(deltaTime);

	if (_stepTimer.HasEnded()) {
		if (_steps < cMaxSteps)
			++_steps;
		else
			_steps = 0;
		_stepTimer.ResetTimer();
	}
}

/* Pos is set to ensure correct value after a GameState is popped */
void Background::Render() {
	_pos.x = -cMaxSteps + _steps;
	AnimatedGameObject::Render();
}

void Background::Clean() {
	AnimatedGameObject::Clean();
}