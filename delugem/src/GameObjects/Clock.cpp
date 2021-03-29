#include "Clock.h"

#include "../TextureManager.h"

#include <cmath>

const char*	     Clock::cPath = "res/images/clock.png";
const Dimensions Clock::cDim  = { 15, 18 };

const char* Clock::cAnimDefault = "Default";

Clock::Clock(Position pos, Timer* timer) {
	
	_connectedTimer = timer;

	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);

	AddAnimation(cAnimDefault, new Animation(0, 16, 0, 0));

	AnimatedGameObject::Init(pos, cDim, objTexture, cAnimDefault, true);
}

/* Manually update current frame to match timer progress */
void Clock::UpdateFrame() {
	_currentAnimation->SetCurrentFrame(std::floor(_connectedTimer->HowMuchPassed() * 16));
}