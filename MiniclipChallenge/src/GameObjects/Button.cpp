#include "Button.h"

#include "../Constants.h"
#include "../TextureManager.h"
#include "../InputHandler.h"

#include <iostream>

Button::Button(float x, float y, int w, int h, std::string filename) {

	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(filename);

	defaultAnimation_ = new Animation(0, 0);
	pressedAnimation_ = new Animation(0, 1);

	GameObject::Init(x, y, w, h, objTexture, defaultAnimation_);
}

void Button::AddContent(GameObject* content) {
	contents_.push_back(content);
}

void Button::Update(int deltaTime) {
	HandleInput();

	for (GameObject* content : contents_) {
		content->Update(deltaTime);
	}
	GameObject::Update(deltaTime);
}

void Button::HandleInput() {
	int mouseX = InputHandler::Instance()->mouseX();
	int mouseY = InputHandler::Instance()->mouseY();
	if (InputHandler::Instance()->mouseLeft() && buttonState_ == ButtonState::DEFAULT) {
		if (mouseX > x_ && mouseX < x_+w_ && mouseY > y_ && mouseY < y_+h_)
			TransitState(ButtonState::PRESSED);
	}
	if (!InputHandler::Instance()->mouseLeft() && buttonState_ == ButtonState::PRESSED) {
		if (mouseX > x_ && mouseX < x_ + w_ && mouseY > y_ && mouseY < y_ + h_)
			TransitState(ButtonState::PRESS_ACTION);
		else
			TransitState(ButtonState::DEFAULT);
	}
}

void Button::Render() {
	GameObject::Render();
	for (GameObject* content : contents_) {
		content->Render();
	}
}

void Button::Clean() {
	for (GameObject* content : contents_) {
		content->Clean();
		delete content;
	}
	delete defaultAnimation_;
	delete pressedAnimation_;
}

Button::ButtonState Button::buttonState() {
	return buttonState_;
}

bool Button::TransitState(ButtonState newButtonState) {
	switch (newButtonState) {
		case ButtonState::DEFAULT:{
			if (buttonState_ == ButtonState::PRESSED) {
				buttonState_ = ButtonState::DEFAULT;
				animation_ = defaultAnimation_;
				return true;
			}
		}
		case ButtonState::PRESSED:{
			if (buttonState_ == ButtonState::DEFAULT) {
				buttonState_ = ButtonState::PRESSED;
				animation_ = pressedAnimation_;
				return true;
			}
		}
		case ButtonState::PRESS_ACTION: {
			if (buttonState_ == ButtonState::PRESSED) {
				buttonState_ = ButtonState::PRESS_ACTION;
				return true;
			}
		}
	}
	std::cout << "Illegal Button Transition from " << int(buttonState_) << " to " << int(newButtonState) << "\n";
	return false;
}