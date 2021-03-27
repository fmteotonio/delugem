#include "Clock.h"

#include "../TextureManager.h"

#include <cmath>
#include <iostream>

const char* Clock::cPath = "res/images/pushclock.png";
const int Clock::cW = 15;
const int Clock::cH = 18;

Clock::Clock(float x, float y, Timer* timer) {
	
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);


	AddAnimation("Default", new Animation(0, 16, 0, 0));

	AnimatedGameObject::Init(x, y, cW, cH, objTexture, "Default", true);

	connectedTimer_ = timer;
}

void Clock::Update() {
	currentAnimation_->SetCurrentFrame(std::floor(connectedTimer_->HowMuchPassed() * 16));
}