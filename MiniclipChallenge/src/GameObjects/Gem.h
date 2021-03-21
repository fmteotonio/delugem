#pragma once

#include "GameObject.h"

class Gem : public GameObject {
public:
	enum class GemColor {
		PINK, BLUE, ORANGE, GREEN, BEIGE
	};

	Gem(GemColor gemColor, float x, float y, int boardX, int boardY, int id);

	int id();
	GemColor gemColor();

	void Update(int deltaTime);
	void Render();

	void Move(float x, float y);
	void MoveB(int boardX, int boardY);

private:
	int id_;
	int boardX_;
	int boardY_;
	GemColor gemColor_;
};