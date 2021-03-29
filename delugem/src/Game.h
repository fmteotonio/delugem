#pragma once

#include "GameStates/GameStateMachine.h"

#include <SDL.h>
#include <SDL_Image.h>

class Game {
public:

	static Game* Instance();
		
	bool IsGameRunning();
	GameStateMachine* GetGameStateMachine();
	SDL_Renderer* GetRenderer();

	bool Init(const char* title, int width, int height);
	void HandleEvents();
	void Update(int deltaTime);
	void Render();
	void Clean();
	void Quit();

private:

	static Game* _gameInstance;
	bool _isGameRunning = false;

	GameStateMachine* _gameStateMachine;
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	void LoadSound();

}; 