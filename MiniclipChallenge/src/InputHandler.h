#pragma once

#include "SDL.h"

class InputHandler {
public:
	static InputHandler* Instance();

	bool GetMouseLeft();
	Sint32 GetMouseX();
	Sint32 GetMouseY();

	void Update();
	void Clean();

private:
	static InputHandler* sInputHandlerInstance_;

	bool mouseLeft_;
	Sint32 mouseX_;
	Sint32 mouseY_;

	InputHandler();
};