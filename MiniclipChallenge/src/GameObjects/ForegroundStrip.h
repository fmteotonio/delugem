#pragma once

#include "AnimatedGameObject.h"

class ForegroundStrip : public AnimatedGameObject {
public:
	static const char* cPath;
	static const int cSourceW;

	static const Dimensions cDim;

	enum class ForegroundStripState {
		DEFAULT, LEVELUP
	};

	ForegroundStrip(Position pos);

	void Update(int deltaTime);
	void Render();

	bool TransitState(ForegroundStripState newForegroundStripState);

private:
	ForegroundStripState foregroundStripState_ = ForegroundStripState::DEFAULT;
};