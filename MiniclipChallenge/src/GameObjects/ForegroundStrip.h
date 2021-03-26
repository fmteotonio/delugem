#pragma once

#include "AnimatedGameObject.h"
#include "../Constants.h"

#include <map>
#include <string>


class ForegroundStrip : public AnimatedGameObject {
public:
	static const char* cPath;
	static const int cW;
	static const int cH;

	enum class ForegroundStripState {
		DEFAULT, LEVELUP
	};

	ForegroundStrip(float x, float y);

	void Update(int deltaTime);

	bool TransitState(ForegroundStripState newForegroundStripState);

private:
	ForegroundStripState foregroundStripState_ = ForegroundStripState::DEFAULT;
};