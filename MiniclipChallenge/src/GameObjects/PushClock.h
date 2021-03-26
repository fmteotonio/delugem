#pragma once

#include "AnimatedGameObject.h"
#include "../Timer.h"

class PushClock : public AnimatedGameObject {
public:
	static const char* cPath;
	static const int cW;
	static const int cH;

	PushClock(float x, float y, Timer* timer);

	void Update();

	Timer* connectedTimer_;
};