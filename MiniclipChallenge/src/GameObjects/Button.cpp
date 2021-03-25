#include "Button.h"

#include "../Constants.h"
#include "../TextureManager.h"
#include "../InputHandler.h"

#include <iostream>

Button::Button(float x, float y, int w, int h, std::string filename) {

	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(filename);

	defaultAnimation_ = new Animation(0, 0);
	hoveredAnimation_ = new Animation(0, 1);
	hovPressedAnimation_ = new Animation(0, 2);
	unhovPressedAnimation_ = new Animation(0, 3);

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
	bool isHovering = mouseX > x_ && mouseX < x_ + w_ && mouseY > y_ && mouseY < y_ + h_;
	bool isClicking = InputHandler::Instance()->mouseLeft();



	// Button States
	if (buttonState_ == ButtonState::PRESS_ACTION)
		TransitState(ButtonState::HOVERED);
	if (isHovering) {
		if (isClicking) {
			if (buttonState_ == ButtonState::HOVERED)
				TransitState(ButtonState::HOV_PRESSED);
			else if (buttonState_ == ButtonState::UNHOV_PRESSED)
				TransitState(ButtonState::HOV_PRESSED);
		}
		else {
			if (buttonState_ == ButtonState::HOV_PRESSED)
				TransitState(ButtonState::PRESS_ACTION);
			if (buttonState_ == ButtonState::DEFAULT)
				TransitState(ButtonState::HOVERED);
		}		
	}
	else {
		if (isClicking) {
			if (buttonState_ == ButtonState::HOV_PRESSED)
				TransitState(ButtonState::UNHOV_PRESSED);
		}
		else {
			if (buttonState_ == ButtonState::UNHOV_PRESSED)
				TransitState(ButtonState::DEFAULT);
			if (buttonState_ == ButtonState::HOVERED)
				TransitState(ButtonState::DEFAULT);
		}
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
	delete hoveredAnimation_;
	delete hovPressedAnimation_;
	delete unhovPressedAnimation_;
}

Button::ButtonState Button::buttonState() {
	return buttonState_;
}

bool Button::TransitState(ButtonState newButtonState) {
	switch (newButtonState) {
		case ButtonState::DEFAULT:{
			if (buttonState_ == ButtonState::HOVERED || buttonState_ == ButtonState::UNHOV_PRESSED || buttonState_ == ButtonState::INACTIVE) {
				buttonState_ = ButtonState::DEFAULT;
				animation_ = defaultAnimation_;
				return true;
			}
			break;
		}
		case ButtonState::HOVERED: {
			if (buttonState_ == ButtonState::DEFAULT || buttonState_ == ButtonState::PRESS_ACTION) {
				buttonState_ = ButtonState::HOVERED;
				animation_ = hoveredAnimation_;
				return true;
			}
			break;
		}
		case ButtonState::HOV_PRESSED:{
			if (buttonState_ == ButtonState::HOVERED || buttonState_ == ButtonState::UNHOV_PRESSED) {
				buttonState_ = ButtonState::HOV_PRESSED;
				animation_ = hovPressedAnimation_;
				return true;
			}
			break;
		}
		case ButtonState::UNHOV_PRESSED: {
			if (buttonState_ == ButtonState::HOV_PRESSED) {
				buttonState_ = ButtonState::UNHOV_PRESSED;
				animation_ = unhovPressedAnimation_;
				return true;
			}
			break;
		}
		case ButtonState::PRESS_ACTION: {
			if (buttonState_ == ButtonState::HOV_PRESSED) {
				buttonState_ = ButtonState::PRESS_ACTION;
				return true;
			}
			break;
		}
		case ButtonState::INACTIVE: {
			buttonState_ = ButtonState::INACTIVE;
			animation_ = unhovPressedAnimation_;
			break;
		}
	}
	std::cout << "Illegal Button Transition from " << int(buttonState_) << " to " << int(newButtonState) << "\n";
	return false;
}