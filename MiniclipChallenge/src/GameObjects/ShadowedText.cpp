#include "ShadowedText.h"

#include "../Constants.h"
#include "../TextureManager.h"

ShadowedText::ShadowedText(float x, float y, Text::Align align, std::string font, int size, std::string text, SDL_Color textColor, SDL_Color shadowColor) {
	text_ = new Text(x, y, align, font, size, text, textColor);
	shadow_ = new Text(x+1, y+1, align, font, size, text, shadowColor);
	GameObject::Init(x, y, 0, 0, nullptr, nullptr);
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

