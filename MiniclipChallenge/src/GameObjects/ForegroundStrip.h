#pragma once

#include "GameObject.h"

class ForegroundStrip : public GameObject {
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

	Animation* defaultAnimation_;
	Animation* levelUpAnimation_;
};