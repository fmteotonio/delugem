#pragma once

#include "GameStates/GameStateMachine.h"

#include "GameObjects/AnimatedGameObject.h"

#include <SDL.h>
#include <SDL_Image.h>

class Game {
public:
	static Game* Instance();
		
	bool bRunning();
	GameStateMachine* gameStateMachine();
	SDL_Renderer* renderer();

	bool Init(const char* title, int width, int height, bool fullscreen);

	void HandleEvents();
	void Quit();

	void Update(int deltaTime);
	void Render();
	void Clean();
	

private:
	static Game* sGameInstance_;
	bool bRunning_ = false;
	GameStateMachine* gameStateMachine_;
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	AnimatedGameObject* background_;
}; 