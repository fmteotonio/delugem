#include "Game.h"

#include "GameStates/TitleScreenState.h"
#include "GameStates/PlayingState.h"
#include "GameObjects/Background.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "GameManager.h"
#include "SoundManager.h"

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>

Game* Game::_gameInstance = nullptr;

Game* Game::Instance() {
	if (!_gameInstance) {
		_gameInstance = new Game();
	}
	return _gameInstance;
}

bool Game::IsGameRunning() { return _isGameRunning; }
GameStateMachine* Game::GetGameStateMachine() { return _gameStateMachine; }
SDL_Renderer* Game::GetRenderer() { return _renderer; }

bool Game::Init(const char* title, int width, int height) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
		if (_window) {
			_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
			if (!_renderer) {
				std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
				return false;
			}
		}
		else {
			std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
			return false;
		}
		_isGameRunning = true;

		TextureManager::Instance();
		if (TTF_Init() != 0) {
			std::cerr << "TTF Init failed: " << SDL_GetError() << std::endl;
			return false;
		}

		InputHandler::Instance();
		SoundManager::Instance()->LoadAllSound();
		GameManager::Instance();

		_gameStateMachine = new GameStateMachine();
		_gameStateMachine->PushState(new TitleScreenState());
		
		return true;
	}
	else {
		std::cerr << "SDL_Init failed.\n";
		return false;
	}
}

void Game::HandleEvents() {
	InputHandler::Instance()->Update();
}

void Game::Update(int deltaTime) {
	_gameStateMachine->Update(deltaTime);
}

void Game::Render() {
	SDL_RenderClear(_renderer);
	_gameStateMachine->Render();
	SDL_RenderPresent(_renderer);
}

void Game::Clean() {
	_gameStateMachine->Clean();

	TextureManager::Instance()->Clean();
	InputHandler::Instance()->Clean();
	SoundManager::Instance()->Clean();
	GameManager::Instance()->Clean();

	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	TTF_Quit();
	SDL_Quit();

	delete _gameStateMachine;
	delete _gameInstance;
}

void Game::Quit() {
	_isGameRunning = false;
}