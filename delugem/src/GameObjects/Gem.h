#pragma once

#include "AnimatedGameObject.h"

class Gem : public AnimatedGameObject{
public:
	static const char* cPath;
	static const Dimensions cDim;
	static const float cAcceleration;
	static const int cNumberOfColors;

	static const char* cAnimDefault;
	static const char* cAnimHovered;
	static const char* cAnimBreaking;
	static const char* cAnimToDestroy;

	enum class GemState {
		DEFAULT, HOVERED, BREAKING, TO_DESTROY
	};
	enum class GemColor {
		PINK, BLUE, ORANGE, GREEN, BEIGE
	};
	
	Gem(Position pos, GemColor gemColor, int id);

	int GetId();
	GemColor GetGemColor();
	GemState GetGemState();
	bool isMoving(bool onXAxis, bool onYAxis);
	
	void MoveTo(Position deltaPos);
	void MoveFrom(Position deltaPos);
	bool TransitState(GemState newGemState);

	void Update(int deltaTime);

private:
	int _id;

	Position _toMove = { 0,0 };
	Position _v = { 0,0 };

	GemColor _gemColor;
	GemState _gemState = GemState::DEFAULT;
};