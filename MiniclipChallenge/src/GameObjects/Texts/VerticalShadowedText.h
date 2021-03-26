#pragma once

#include "../GameObject.h"
#include "Text.h"

#include <string>
#include <vector>

class VerticalShadowedText : public GameObject {
public:
	VerticalShadowedText(float x, float y, Text::Align align, std::string font, int size, int spacing, std::string text, SDL_Color textColor, SDL_Color shadowColor);

	std::vector<GameObject*> text_;

	void Update(int deltaTime);
	void Render();
	void Clean();
};