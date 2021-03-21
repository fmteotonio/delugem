#pragma once

#include "GameObjects/GameObject.h"

#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_Image.h>

class Game {
public:
	static Game* Instance();
		
	bool bRunning();
	SDL_Renderer* renderer();

	bool Init(const char* title, int width, int height, bool fullscreen);

	void HandleEvents();
	void Quit();

	void Update(int deltaTime);
	void Render();
	void Clean();
	

private:
	static Game* spInstance_;
	bool bRunning_;
	std::vector<GameObject*> gameObjects_;
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	Game();
}; 