#include "Game.h"

#include "GameObjects/Background.h"
#include "GameObjects/Board.h"
#include "GameObjects/Gem.h"
#include "GameStates/TitleScreenState.h"
#include "GameStates/PlayingState.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "GameManager.h"

#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>

Game* Game::sGameInstance_ = nullptr;

Game* Game::Instance() {
	if (!sGameInstance_) {
		sGameInstance_ = new Game();
	}
	return sGameInstance_;
}

bool Game::bRunning() { return bRunning_; }
GameStateMachine* Game::gameStateMachine() { return gameStateMachine_; }
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

		//INIT TEX MAN

		TextureManager::Instance();
	
		if (TTF_Init() != 0) {
			std::cout << "TTF Init failed.\n";
			return false;
		}


		//INIT INPUT HANDLER
		InputHandler::Instance();

		//INIT GAME_STATE

		GameManager::Instance();

		gameStateMachine_ = new GameStateMachine();
		gameStateMachine_->pushState(new TitleScreenState());
		
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
	gameStateMachine_->Update(deltaTime);
}

void Game::Render() {
	SDL_RenderClear(renderer_);
	gameStateMachine_->Render();
	SDL_RenderPresent(renderer_);
}

void Game::Clean() {
	
	TextureManager::Instance()->Clean();
	InputHandler::Instance()->Clean();

	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer_);
	TTF_Quit();
	SDL_Quit();

	delete gameStateMachine_;
	delete sGameInstance_;
}

Game::Game() {
	bRunning_ = false;
	gameStateMachine_ = nullptr;
	window_ = nullptr;
	renderer_ = nullptr;
};