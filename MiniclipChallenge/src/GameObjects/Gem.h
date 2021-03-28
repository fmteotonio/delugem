#pragma once

#include "AnimatedGameObject.h"

class Gem : public AnimatedGameObject{
public:
	static const char* cPath;
	static const Dimensions cDim;
	static const int cAcceleration;
	static const int cNumberOfColors;

	enum class GemState {
		DEFAULT, HOVERED, BREAKING, TO_DESTROY
	};
	enum class GemColor {
		PINK, BLUE, ORANGE, GREEN, BEIGE
	};
	
	Gem(GemColor gemColor, Position pos, int id);

	int GetId();
	GemColor GetGemColor();
	GemState GetGemState();

	bool isMoving();
	void Move(float x, float y);	
	void MoveFrom(float x, float y);
	
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