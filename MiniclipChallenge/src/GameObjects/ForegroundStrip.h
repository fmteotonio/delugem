#pragma once

#include "AnimatedGameObject.h"
#include <map>
#include <string>

class ForegroundStrip : public AnimatedGameObject {
public:
	enum class ForegroundStripState {
		DEFAULT, LEVELUP
	};

	ForegroundStrip(float x, float y);

	void Update(int deltaTime);
	void Render();
	void Clean();
	bool TransitState(ForegroundStripState newForegroundStripState);

private:

	ForegroundStripState foregroundStripState_ = ForegroundStripState::DEFAULT;
};