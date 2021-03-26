#include "Button.h"

#include "../../Constants.h"
#include "../../TextureManager.h"
#include "../../InputHandler.h"

#include <iostream>

Button::Button(float x, float y, int w, int h, std::string filename) {

	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(filename);

	addAnimation("Default",	     new Animation(0, 0));
	addAnimation("Hovered",      new Animation(0, 1));
	addAnimation("HovPressed",   new Animation(0, 2));
	addAnimation("UnhovPressed", new Animation(0, 3));

	AnimatedGameObject::Init(x, y, w, h, objTexture, "Default", false);
}

void Button::AddContent(GameObject* content) {
	contents_.push_back(content);
}

void Button::Update(int deltaTime) {
	HandleInput();
	for (GameObject* content : contents_) {
		content->Update(deltaTime);
	}
	AnimatedGameObject::Update(deltaTime);
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
	AnimatedGameObject::Render();
	for (GameObject* content : contents_) {
		content->Render();
	}
}

void Button::Clean() {
	for (GameObject* content : contents_) {
		content->Clean();
		delete content;
	}
	AnimatedGameObject::Clean();
}

Button::ButtonState Button::buttonState() {
	return buttonState_;
}

bool Button::TransitState(ButtonState newButtonState) {
	switch (newButtonState) {
		case ButtonState::DEFAULT:{
			if (buttonState_ == ButtonState::HOVERED || buttonState_ == ButtonState::UNHOV_PRESSED || buttonState_ == ButtonState::INACTIVE) {
				buttonState_ = ButtonState::DEFAULT;
				setAnimation("Default", false);
				return true;
			}
			break;
		}
		case ButtonState::HOVERED: {
			if (buttonState_ == ButtonState::DEFAULT || buttonState_ == ButtonState::PRESS_ACTION) {
				buttonState_ = ButtonState::HOVERED;
				setAnimation("Hovered", false);
				return true;
			}
			break;
		}
		case ButtonState::HOV_PRESSED:{
			if (buttonState_ == ButtonState::HOVERED || buttonState_ == ButtonState::UNHOV_PRESSED) {
				buttonState_ = ButtonState::HOV_PRESSED;
				setAnimation("HovPressed", false);
				return true;
			}
			break;
		}
		case ButtonState::UNHOV_PRESSED: {
			if (buttonState_ == ButtonState::HOV_PRESSED) {
				buttonState_ = ButtonState::UNHOV_PRESSED;
				setAnimation("UnhovPressed", false);
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
			setAnimation("UnhovPressed", false);
			break;
		}
	}
	std::cout << "Illegal Button Transition from " << int(buttonState_) << " to " << int(newButtonState) << "\n";
	return false;
}