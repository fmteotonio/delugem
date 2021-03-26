#pragma once

#include "AnimatedGameObject.h"

class ForegroundStrip : public AnimatedGameObject {
public:
	static const char* cPath;
	static const int cW;
	static const int cH;
	static const int cSourceW;

	enum class ForegroundStripState {
		DEFAULT, LEVELUP
	};

	ForegroundStrip(float x, float y);

	void Update(int deltaTime);
	void Render();

	bool TransitState(ForegroundStripState newForegroundStripState);

private:
	ForegroundStripState foregroundStripState_ = ForegroundStripState::DEFAULT;
};