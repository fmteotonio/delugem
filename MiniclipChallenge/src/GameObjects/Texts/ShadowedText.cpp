#include "ShadowedText.h"

ShadowedText::ShadowedText(Position pos, Text::Align align, std::string font, int size, std::string text, SDL_Color textColor, SDL_Color shadowColor) {
	text_ = new Text(pos, align, font, size, text, textColor);
	shadow_ = new Text({ pos.x + 1, pos.y + 1 }, align, font, size, text, shadowColor);
	GameObject::Init(pos);
}

void ShadowedText::Update(int deltaTime) {
	shadow_->Update(deltaTime);
	text_->Update(deltaTime);
}

void ShadowedText::Render() {
	shadow_->Render();
	text_->Render();
}

void ShadowedText::Clean() {
	delete shadow_;
	delete text_;
}

