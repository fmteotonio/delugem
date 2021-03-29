#pragma once

#include <string>

#include "../AnimatedGameObject.h"

class Text : public AnimatedGameObject {
public:

	static const char* cAnimDefault;

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

	Text(Position pos, Align align, std::string font, int size, std::string text, SDL_Color color);
};