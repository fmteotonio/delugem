#include "PushClock.h"

#include "../TextureManager.h"

#include <cmath>
#include <iostream>

const char* PushClock::cPath = "res/images/pushclock.png";
const int PushClock::cW = 15;
const int PushClock::cH = 18;

PushClock::PushClock(float x, float y, Timer* timer) {
	
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(cPath);


	AddAnimation("Default", new Animation(0, 16, 0, 0));

	AnimatedGameObject::Init(x, y, cW, cH, objTexture, "Default", true);

	connectedTimer_ = timer;
}

void PushClock::Update() {
	currentAnimation_->SetCurrentFrame(std::floor(connectedTimer_->HowMuchPassed() * 16));
}