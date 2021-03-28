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
	static InputHandler* sInputHandlerInstance;

	bool _mouseLeft;
	Sint32 _mouseX;
	Sint32 _mouseY;

	InputHandler();
};