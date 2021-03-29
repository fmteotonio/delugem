#pragma once

#include "AnimatedGameObject.h"
#include "../Timer.h"

class Background : public AnimatedGameObject {
public:

	static const char* cPath;
	static const int cMaxSteps;
	static const int cTimePerStep;
	static const Dimensions cDim;

	static const char* cAnimDefault;

	Background(Position pos);

	void Update(int deltaTime);
	void Clean();

private:

	int _steps = 0;
	Timer* _stepTimer;

};