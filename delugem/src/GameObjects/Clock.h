#pragma once

#include "AnimatedGameObject.h"
#include "../Timer.h"

class Clock : public AnimatedGameObject {
public:

	static const char* cPath;
	static const Dimensions cDim;

	static const char* cAnimDefault;

	Clock(Position pos, Timer* timer);

	void UpdateFrame();

private:

	Timer* _connectedTimer;

};