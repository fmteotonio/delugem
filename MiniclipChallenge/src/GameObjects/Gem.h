#pragma once

#include "GameObject.h"
#include "../Animation.h"

class Gem : public GameObject {
public:
	enum class GemColor {
		PINK, BLUE, ORANGE, GREEN, BEIGE
	};
	enum class GemStatus {
		DEFAULT, DESTROY_ANIMATION, TO_DESTROY
	};

	Gem(GemColor gemColor, float x, float y, int boardX, int boardY, int id);

	int id();
	GemColor gemColor();
	GemStatus gemStatus();

	void Update(int deltaTime);
	void Render();

	void Move(float x, float y);
	void MoveB(int boardX, int boardY);

	void DestroyGem();

private:
	int id_;
	int boardX_;
	int boardY_;
	GemColor gemColor_;
	
	//AnimationTests
	GemStatus gemStatus_;

	Animation* stillAnimation;
	Animation* destroyAnimation;

	//bool destroyAnimationStarted_;
	//int destroyAnimationSpeed_;
	//int destroyAnimationFrameNumber_;
	//int destroyAnimationStartTime_;
};