#include "Game.h"

#include "GameObjects/Background.h"
#include "GameObjects/Board.h"
#include "GameObjects/Gem.h"
#include "InputHandler.h"
#include "TextureManager.h"

#include <SDL.h>
#include <SDL_Image.h>

Game* Game::spInstance_ = nullptr;

Game* Game::Instance() {
	if (!spInstance_) {
		spInstance_ = new Game();
	}
	return spInstance_;
}

bool Game::bRunning() { return bRunning_; }
SDL_Renderer* Game::renderer() { return renderer_; }

bool Game::Init(const char* title, int width, int height, bool fullscreen) {
	//INIT WINDOW AND RENDERER

	int flags = 0;
	
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (window_) {
			std::cout << "Window created successfully.\n";
			renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
			if (renderer_) {
				std::cout << "Renderer created successfully.\n";
				SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
			}
			else {
				std::cout << "Renderer creation failed.\n";
				return false;
			}
		}
		else {
			std::cout << "Window creation failed.\n";
			return false;
		}
		std::cout << "SDL_Init successful.\n";
		bRunning_ = true;
	
		//INIT INPUT HANDLER
		InputHandler::Instance();

		//INIT GAMEOBJECTS

		gameObjects_.push_back(new Background(0, 0));
		gameObjects_.push_back(new Board(350, 56));
		
		return true;
		//----------------------------------
	}
	else {
		std::cout << "SDL_Init failed.\n";
		return false;
	}
}

void Game::HandleEvents() {
	InputHandler::Instance()->Update();
}

void Game::Quit() {
	bRunning_ = false;
}

void Game::Update(int deltaTime) {
	for (GameObject* gameObjectPointer : gameObjects_) {
		gameObjectPointer->Update(deltaTime);
	}
}

void Game::Render() {
	SDL_RenderClear(renderer_);
	for (GameObject* gameObjectPointer : gameObjects_) {
		gameObjectPointer->Render();
	}
	SDL_RenderPresent(renderer_);
}

void Game::Clean() {
	for (GameObject* gameObjectPointer : gameObjects_) {
		delete gameObjectPointer;
	}
	InputHandler::Instance()->Clean();

	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer_);
	SDL_Quit();

	delete spInstance_;
}

Game::Game() {
	bRunning_ = false;
	gameObjects_ = {};
	window_ = nullptr;
	renderer_ = nullptr;
};