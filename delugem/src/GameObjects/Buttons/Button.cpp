#include "Button.h"

#include "../../Constants.h"
#include "../../TextureManager.h"
#include "../../InputHandler.h"

#include <iostream>

const char* Button::cAnimDefault      = "Default";
const char* Button::cAnimHovered      = "Hovered";
const char* Button::cAnimHovPressed   = "HovPressed";
const char* Button::cAnimUnhovPressed = "UnhovPressed";

Button::Button(Position pos, Dimensions dim, std::string filename) {
	
	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(filename);

	AddAnimation(cAnimDefault,	    new Animation(0, 0));
	AddAnimation(cAnimHovered,      new Animation(0, 1));
	AddAnimation(cAnimHovPressed,   new Animation(0, 2));
	AddAnimation(cAnimUnhovPressed, new Animation(0, 3));

	AnimatedGameObject::Init(pos, dim, objTexture, cAnimDefault, false);
}

Button::ButtonState Button::GetButtonState() {
	return _buttonState;
}

void Button::AddContent(GameObject* content) {
	_contents.push_back(content);
}

bool Button::TransitState(ButtonState newButtonState) {
	switch (newButtonState) {
		case ButtonState::DEFAULT:{
			if (_buttonState == ButtonState::HOVERED || _buttonState == ButtonState::UNHOV_PRESSED || _buttonState == ButtonState::INACTIVE) {
				_buttonState = ButtonState::DEFAULT;
				SetAnimation(cAnimDefault, false);
				return true;
			}
			break;
		}
		case ButtonState::HOVERED: {
			if (_buttonState == ButtonState::DEFAULT || _buttonState == ButtonState::PRESS_ACTION) {
				_buttonState = ButtonState::HOVERED;
				SetAnimation(cAnimHovered, false);
				return true;
			}
			break;
		}
		case ButtonState::HOV_PRESSED:{
			if (_buttonState == ButtonState::HOVERED || _buttonState == ButtonState::UNHOV_PRESSED) {
				_buttonState = ButtonState::HOV_PRESSED;
				SetAnimation(cAnimHovPressed, false);
				return true;
			}
			break;
		}
		//Unhovered pressed state to allow click cancelling by releasing outside range
		case ButtonState::UNHOV_PRESSED: {
			if (_buttonState == ButtonState::HOV_PRESSED) {
				_buttonState = ButtonState::UNHOV_PRESSED;
				SetAnimation(cAnimUnhovPressed, false);
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
			SetAnimation(cAnimUnhovPressed, false);
			return true;
		}
	}
	std::cerr << "Illegal Button Transition from " << int(_buttonState) << " to " << int(newButtonState) << "\n";
	return false;
}

/* Sets button active if condition verifies, or inactive otherwise */
void Button::OnlySetActiveIf(bool condition) {
	if (!condition && GetButtonState() != Button::ButtonState::INACTIVE)
		TransitState(Button::ButtonState::INACTIVE);
	else if (condition && GetButtonState() == Button::ButtonState::INACTIVE)
		TransitState(Button::ButtonState::DEFAULT);
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
	bool isHovering = mouseX > _pos.x && mouseX < _pos.x + _destDim.w && mouseY > _pos.y && mouseY < _pos.y + _destDim.h;
	bool isClicking = InputHandler::Instance()->GetMouseLeft();

	// Handling State Transitions
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
