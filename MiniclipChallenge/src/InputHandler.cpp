#include "InputHandler.h"

#include "Game.h"

#include <iostream>

InputHandler* InputHandler::sInputHandlerInstance_ = nullptr;

InputHandler* InputHandler::Instance() {
	if (!sInputHandlerInstance_) {
		sInputHandlerInstance_ = new InputHandler();
	}
	return sInputHandlerInstance_;
}

bool   InputHandler::mouseLeft() { return mouseLeft_; }
Sint32 InputHandler::mouseX() { return mouseX_; }
Sint32 InputHandler::mouseY() { return mouseY_; }

void InputHandler::Update() {
	SDL_Event event;


	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				mouseLeft_ = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				mouseLeft_ = false;
			}
			break;
		case SDL_MOUSEMOTION :
			mouseX_ = event.motion.x;  
			mouseY_ = event.motion.y;
			break;
		case SDL_QUIT:
			Game::Instance()->Quit();
			break;
		default:
			break;
		}

	}
}

void InputHandler::Clean() {
	delete sInputHandlerInstance_;
}

InputHandler::InputHandler() {
	mouseLeft_ = false;
	mouseX_ = 0;
	mouseY_ = 0;
}