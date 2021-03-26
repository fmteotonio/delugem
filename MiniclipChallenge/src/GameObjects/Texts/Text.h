#pragma once

#include "../AnimatedGameObject.h"

#include <string>

class Text : public AnimatedGameObject {
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
};