#pragma once

#include "GameStates/GameStateMachine.h"

#include "GameObjects/AnimatedGameObject.h"

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
	void Quit();

	void Update(int deltaTime);
	void Render();
	void Clean();
	

private:
	static Game* sGameInstance;
	bool _isGameRunning = false;

	GameStateMachine* _gameStateMachine;
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	AnimatedGameObject* _background;
}; 