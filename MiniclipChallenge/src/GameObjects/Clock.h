#pragma once

#include "AnimatedGameObject.h"
#include "../Timer.h"

class Clock : public AnimatedGameObject {
public:
	static const char* cPath;
	static const int cW;
	static const int cH;

	Clock(float x, float y, Timer* timer);

	void UpdateFrame();

	Timer* connectedTimer_;
};