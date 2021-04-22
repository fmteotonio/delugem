#pragma once

#include "AnimatedGameObject.h"

class ForegroundStrip : public AnimatedGameObject {
public:

	static const char* cPath;
	static const Dimensions cSrcDim;
	static const Dimensions cDestDim;

	static const char* cAnimDefault;
	static const char* cAnimLevelUp;

	enum class ForegroundStripState {
		DEFAULT, LEVELUP
	};

	ForegroundStrip(Position pos);

	bool TransitState(ForegroundStripState newForegroundStripState);

	void Update(int deltaTime);

private:
	
	ForegroundStripState _foregroundStripState = ForegroundStripState::DEFAULT;

};