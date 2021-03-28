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

	bool isMoving(bool onXAxis, bool onYAxis);
	void Move(Position pos);
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