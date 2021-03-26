#include "InputHandler.h"

#include "Constants.h"
#include "Game.h"

InputHandler* InputHandler::sInputHandlerInstance_ = nullptr;

InputHandler* InputHandler::Instance() {
	if (!sInputHandlerInstance_) {
		sInputHandlerInstance_ = new InputHandler();
	}
	return sInputHandlerInstance_;
}

bool   InputHandler::GetMouseLeft() { return mouseLeft_; }
Sint32 InputHandler::GetMouseX() { return mouseX_ / GAME_SCALE; }
Sint32 InputHandler::GetMouseY() { return mouseY_ / GAME_SCALE; }

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