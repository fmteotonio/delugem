#pragma once

#include "GameObject.h"
#include "../Animation.h"
#include "../Constants.h"

class Gem : public GameObject{
public:
	enum class GemState {
		DEFAULT, HOVERED, BREAKING, TO_DESTROY
	};
	enum class GemColor {
		PINK, BLUE, ORANGE, GREEN, BEIGE
	};
	

	Gem(GemColor gemColor, float x, float y, int id);

	int id();
	GemColor gemColor();
	GemState gemState();

	void Move(float x, float y);
	bool isMoving();

	void Update(int deltaTime);
	void Render();
	void Clean();

	bool TransitState(GemState newGemState);

private:

	int id_;

	float toMoveX_ = 0;
	float toMoveY_ = 0;
	float vx_ = 0;
	float vy_ = 0;
	float a_ = GEM_ACCELERATION;

	GemColor gemColor_;
	GemState gemState_ = GemState::DEFAULT;

	Animation* defaultAnimation_;
	Animation* hoveredAnimation_;
	Animation* breakingAnimation_;
	Animation* toDestroyAnimation_;
};