#include "Clock.h"

#include "../TextureManager.h"

#include <cmath>
#include <iostream>

const char* Clock::cPath = "res/images/clock.png";
const Dimensions Clock::cDim = { 15, 18 };

Clock::Clock(Position pos, Timer* timer) {
	
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);

	AddAnimation("Default", new Animation(0, 16, 0, 0));

	AnimatedGameObject::Init(pos, cDim, objTexture, "Default", true);

	_connectedTimer = timer;
}

void Clock::UpdateFrame() {
	_currentAnimation->SetCurrentFrame(std::floor(_connectedTimer->HowMuchPassed() * 16));
}