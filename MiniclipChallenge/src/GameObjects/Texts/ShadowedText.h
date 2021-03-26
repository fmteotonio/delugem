#pragma once

#include "../GameObject.h"
#include "Text.h"

#include <string>

class ShadowedText : public GameObject {
public:
	ShadowedText(float x, float y, Text::Align align, std::string font, int size, std::string text, SDL_Color textColor, SDL_Color shadowColor);

	Text* text_;
	Text* shadow_;

	void Update(int deltaTime);
	void Render();
	void Clean();
};