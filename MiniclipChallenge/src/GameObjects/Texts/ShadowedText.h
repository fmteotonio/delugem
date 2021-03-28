#pragma once

#include <string>

#include "../GameObject.h"
#include "Text.h"

class ShadowedText : public GameObject {
public:
	ShadowedText(Position pos, Text::Align align, std::string font, int size, std::string text, SDL_Color textColor, SDL_Color shadowColor);

	Text* _text;
	Text* _shadow;

	void Update(int deltaTime);
	void Render();
	void Clean();
};