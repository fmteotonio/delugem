#pragma once

#include "AnimatedGameObject.h"
#include "../Timer.h"

class Background : public AnimatedGameObject {
public:
	static const char* cPath_;
	static const int cMaxSteps_;
	static const int cTimePerStep_;
	static const int cW;
	static const int cH;

	Background(float x, float y);

	void Update(int deltaTime);
private:
	int steps_ = 0;
	Timer* stepTimer_;
};