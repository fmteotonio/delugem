#include "Button.h"

#include "../../Constants.h"
#include "../../TextureManager.h"
#include "../../InputHandler.h"

#include <iostream>

Button::Button(Position pos, Dimensions dim, std::string filename) {

	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(filename);

	AddAnimation("Default",	     new Animation(0, 0));
	AddAnimation("Hovered",      new Animation(0, 1));
	AddAnimation("HovPressed",   new Animation(0, 2));
	AddAnimation("UnhovPressed", new Animation(0, 3));

	AnimatedGameObject::Init(pos, dim, objTexture, "Default", false);
}

void Button::AddContent(GameObject* content) {
	_contents.push_back(content);
}

void Button::Update(int deltaTime) {
	HandleInput();
	for (GameObject* content : _contents) {
		content->Update(deltaTime);
	}
	AnimatedGameObject::Update(deltaTime);
}

void Button::HandleInput() {
	int mouseX = InputHandler::Instance()->GetMouseX();
	int mouseY = InputHandler::Instance()->GetMouseY();
	bool isHovering = mouseX > _pos.x && mouseX < _pos.x + _dim.w && mouseY > _pos.y && mouseY < _pos.y + _dim.h;
	bool isClicking = InputHandler::Instance()->GetMouseLeft();



	// Button States
	if (_buttonState == ButtonState::PRESS_ACTION)
		TransitState(ButtonState::HOVERED);
	if (isHovering) {
		if (isClicking) {
			if (_buttonState == ButtonState::HOVERED)
				TransitState(ButtonState::HOV_PRESSED);
			else if (_buttonState == ButtonState::UNHOV_PRESSED)
				TransitState(ButtonState::HOV_PRESSED);
		}
		else {
			if (_buttonState == ButtonState::HOV_PRESSED)
				TransitState(ButtonState::PRESS_ACTION);
			if (_buttonState == ButtonState::DEFAULT)
				TransitState(ButtonState::HOVERED);
		}		
	}
	else {
		if (isClicking) {
			if (_buttonState == ButtonState::HOV_PRESSED)
				TransitState(ButtonState::UNHOV_PRESSED);
		}
		else {
			if (_buttonState == ButtonState::UNHOV_PRESSED)
				TransitState(ButtonState::DEFAULT);
			if (_buttonState == ButtonState::HOVERED)
				TransitState(ButtonState::DEFAULT);
		}
	}
	
}

void Button::Render() {
	AnimatedGameObject::Render();
	for (GameObject* content : _contents) {
		content->Render();
	}
}

void Button::Clean() {
	for (GameObject* content : _contents) {
		content->Clean();
		delete content;
	}
	AnimatedGameObject::Clean();
}

Button::ButtonState Button::GetButtonState() {
	return _buttonState;
}

bool Button::TransitState(ButtonState newButtonState) {
	switch (newButtonState) {
		case ButtonState::DEFAULT:{
			if (_buttonState == ButtonState::HOVERED || _buttonState == ButtonState::UNHOV_PRESSED || _buttonState == ButtonState::INACTIVE) {
				_buttonState = ButtonState::DEFAULT;
				SetAnimation("Default", false);
				return true;
			}
			break;
		}
		case ButtonState::HOVERED: {
			if (_buttonState == ButtonState::DEFAULT || _buttonState == ButtonState::PRESS_ACTION) {
				_buttonState = ButtonState::HOVERED;
				SetAnimation("Hovered", false);
				return true;
			}
			break;
		}
		case ButtonState::HOV_PRESSED:{
			if (_buttonState == ButtonState::HOVERED || _buttonState == ButtonState::UNHOV_PRESSED) {
				_buttonState = ButtonState::HOV_PRESSED;
				SetAnimation("HovPressed", false);
				return true;
			}
			break;
		}
		case ButtonState::UNHOV_PRESSED: {
			if (_buttonState == ButtonState::HOV_PRESSED) {
				_buttonState = ButtonState::UNHOV_PRESSED;
				SetAnimation("UnhovPressed", false);
				return true;
			}
			break;
		}
		case ButtonState::PRESS_ACTION: {
			if (_buttonState == ButtonState::HOV_PRESSED) {
				_buttonState = ButtonState::PRESS_ACTION;
				return true;
			}
			break;
		}
		case ButtonState::INACTIVE: {
			_buttonState = ButtonState::INACTIVE;
			SetAnimation("UnhovPressed", false);
			return true;
		}
	}
	std::cerr << "Illegal Button Transition from " << int(_buttonState) << " to " << int(newButtonState) << "\n";
	return false;
}

void Button::OnlySetActiveIf(bool condition) {
	if (!condition && GetButtonState() != Button::ButtonState::INACTIVE)
		TransitState(Button::ButtonState::INACTIVE);
	else if (condition && GetButtonState() == Button::ButtonState::INACTIVE)
		TransitState(Button::ButtonState::DEFAULT);
}