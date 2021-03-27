#include "VerticalShadowedText.h"

#include "ShadowedText.h"

VerticalShadowedText::VerticalShadowedText(float x, float y, Text::Align align, std::string font, int size, int spacing, std::string text, SDL_Color textColor, SDL_Color shadowColor) {
	
	int i = 0;
	for (char character : text) {
		std::string characterString(1, character);
		text_.push_back(new ShadowedText(x, y+(size+spacing)*i, align, font, size, characterString, textColor, shadowColor));
		++i;
	}
	GameObject::Init(x, y);
}

void VerticalShadowedText::Update(int deltaTime) {
	for (GameObject* character : text_) {
		character->Update(deltaTime);
	}
}

void VerticalShadowedText::Render() {
	for (GameObject* character : text_) {
		character->Render();
	}
}

void VerticalShadowedText::Clean() {
	for (GameObject* character : text_) {
		character->Clean();
	}
}
