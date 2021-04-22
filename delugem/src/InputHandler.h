#pragma once

#include <SDL.h>

class InputHandler {
public:

	static InputHandler* Instance();

	bool GetMouseLeft();
	Sint32 GetMouseX();
	Sint32 GetMouseY();

	void Update();
	void Clean();

private:

	static InputHandler* _inputHandlerInstance;

	bool _mouseLeft = false;
	Sint32 _mouseX = 0;
	Sint32 _mouseY = 0;

};