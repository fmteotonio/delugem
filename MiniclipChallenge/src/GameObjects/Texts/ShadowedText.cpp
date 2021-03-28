#include "ShadowedText.h"

ShadowedText::ShadowedText(Position pos, Text::Align align, std::string font, int size, std::string text, SDL_Color textColor, SDL_Color shadowColor) {
	_text = new Text(pos, align, font, size, text, textColor);
	_shadow = new Text({ pos.x + 1, pos.y + 1 }, align, font, size, text, shadowColor);
	GameObject::Init(pos);
}

void ShadowedText::Update(int deltaTime) {
	_shadow->Update(deltaTime);
	_text->Update(deltaTime);
}

void ShadowedText::Render() {
	_shadow->Render();
	_text->Render();
}

void ShadowedText::Clean() {
	delete _shadow;
	delete _text;
}

