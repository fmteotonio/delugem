#pragma once

#include "GameObject.h"
#include "../Animation.h"
#include "../Constants.h"

class Gem : public GameObject {
public:
	enum class GemColor {
		PINK, BLUE, ORANGE, GREEN, BEIGE
	};
	enum class GemStatus {
		DEFAULT, DESTROY_ANIMATION, TO_DESTROY
	};

	Gem(GemColor gemColor, float x, float y, int id);

	int id();
	GemColor gemColor();
	GemStatus gemStatus();

	void Move(float x, float y);
	void DestroyGem();

	void Update(int deltaTime);
	void Render();
	void Clean();

private:
	int id_;

	float toMoveX_ = 0;
	float toMoveY_ = 0;
	float vx_ = 0;
	float vy_ = 0;
	float a_ = GEM_ACCELERATION;

	GemColor gemColor_;
	GemStatus gemStatus_;

	Animation* stillAnimation_;
	Animation* destroyAnimation_;
};