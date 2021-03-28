#pragma once

#include "AnimatedGameObject.h"
#include "../Timer.h"

class Clock : public AnimatedGameObject {
public:
	static const char* cPath;
	static const Dimensions cDim;

	Clock(Position pos, Timer* timer);

	void UpdateFrame();

	Timer* _connectedTimer;
};