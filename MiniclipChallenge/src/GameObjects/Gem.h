#pragma once

#include "AnimatedGameObject.h"
#include "../Animation.h"
#include "../Constants.h"

class Gem : public AnimatedGameObject{
public:
	static const char* cPath;
	static const int cW;
	static const int cH;
	static const int cAcceleration;
	static const int cNumberOfColors;

	enum class GemState {
		DEFAULT, HOVERED, BREAKING, TO_DESTROY
	};
	enum class GemColor {
		PINK, BLUE, ORANGE, GREEN, BEIGE
	};
	
	Gem(GemColor gemColor, float x, float y, int id);

	int GetId();
	GemColor GetGemColor();
	float GetY();
	void SetY(float y);
	void Move(float x, float y);
	bool isMoving();

	GemState GetGemState();
	bool TransitState(GemState newGemState);

	void Update(int deltaTime);

private:
	int id_;

	float toMoveX_ = 0;
	float toMoveY_ = 0;
	float vx_ = 0;
	float vy_ = 0;

	GemColor gemColor_;
	GemState gemState_ = GemState::DEFAULT;
};