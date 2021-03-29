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

	Background();

	void Update(int deltaTime);
	void Render();
	void Clean();

private:

	static int _steps;
	static Timer _stepTimer;

};