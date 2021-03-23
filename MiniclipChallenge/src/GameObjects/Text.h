#pragma once

#include "GameObject.h"

#include <string>

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

	Text(float x, float y, Align align, std::string font, int size, std::string text, SDL_Color color);

	void Update(int deltaTime);
	void Render();
	void Clean();
};