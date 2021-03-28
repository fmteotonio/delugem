#include "VerticalShadowedText.h"

#include "ShadowedText.h"

VerticalShadowedText::VerticalShadowedText(Position pos, Text::Align align, std::string font, int size, int spacing, std::string text, SDL_Color textColor, SDL_Color shadowColor) {
	
	int i = 0;
	for (char character : text) {
		std::string characterString(1, character);
		_textObjects.push_back(new ShadowedText({ pos.x, pos.y + (size + spacing) * i }, align, font, size, characterString, textColor, shadowColor));
		++i;
	}
	GameObject::Init(pos);
}

void VerticalShadowedText::Update(int deltaTime) {
	for (GameObject* character : _textObjects) {
		character->Update(deltaTime);
	}
}

void VerticalShadowedText::Render() {
	for (GameObject* character : _textObjects) {
		character->Render();
	}
}

void VerticalShadowedText::Clean() {
	for (GameObject* character : _textObjects) {
		character->Clean();
	}
}

