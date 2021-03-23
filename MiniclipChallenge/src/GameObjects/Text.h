#pragma once

#include "GameObject.h"

class Text : public GameObject {
public:
	enum class Align {
		UPLEFT,
		UP,
		UPRIGHT,
		MIDLEFT,
		MID,
		MIDRIGHT,
		DOWNLEFT,
		DOWN,
		DOWNRIGHT
	};

	Text(float x, float y, Align align, std::string font, int size, std::string text, int r, int g, int b);

	void Update(int deltaTime);
	void Render();
	void Clean();
};