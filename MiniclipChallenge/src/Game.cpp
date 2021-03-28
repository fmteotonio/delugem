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

#define MUS_ONLYTRACK		"res/sounds/visager_shoots.mp3"
#define SND_BREAK			"res/sounds/break.wav"
#define SND_PUSHCOLUMN		"res/sounds/columnpush.wav"
#define SND_FILL			"res/sounds/fill.wav"
#define SND_GAMEOVER		"res/sounds/gameover.wav"
#define SND_GAMESTART		"res/sounds/gamestart.wav"
#define SND_LEVELUP			"res/sounds/levelup.wav"
#define SND_PIECEFALL		"res/sounds/piecefall.wav"
#define SND_BUTTONSELECT	"res/sounds/buttonselect.wav"
#define SND_GEMSFALLTITLE	"res/sounds/gemsfalltitle.wav"


Game* Game::sGameInstance = nullptr;

Game* Game::Instance() {
	if (!sGameInstance) {
		sGameInstance = new Game();
	}
	return sGameInstance;
}

bool Game::IsGameRunning() { return _isGameRunning; }
GameStateMachine* Game::GetGameStateMachine() { return _gameStateMachine; }
SDL_Renderer* Game::GetRenderer() { return _renderer; }

bool Game::Init(const char* title, int width, int height, bool fullscreen) {
	//INIT WINDOW AND RENDERER

	int flags = 0;
	
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (_window) {
			_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
			if (_renderer) {
				SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
			}
			else {
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
		SoundManager::Instance();
		GameManager::Instance();

		//SoundManager::Instance()->Load(MUS_ONLYTRACK,"onlyTrack",SoundManager::soundType::MUSIC,4);
		//SoundManager::Instance()->PlayMusic("onlyTrack", 1);
		//SoundManager::Instance()->SetMusicPosition(33.5);

		//Load SFX
		SoundManager::Instance()->Load(SND_BREAK,     "Break",     SoundManager::soundType::SFX, 8);
		SoundManager::Instance()->Load(SND_PUSHCOLUMN,"PushColumn",SoundManager::soundType::SFX, 8);
		SoundManager::Instance()->Load(SND_FILL,      "Fill",      SoundManager::soundType::SFX, 12);
		SoundManager::Instance()->Load(SND_GAMEOVER,  "GameOver",  SoundManager::soundType::SFX, 16);
		SoundManager::Instance()->Load(SND_GAMESTART, "GameStart", SoundManager::soundType::SFX, 12);
		SoundManager::Instance()->Load(SND_LEVELUP,	  "LevelUp",   SoundManager::soundType::SFX, 8);
		SoundManager::Instance()->Load(SND_PIECEFALL, "PieceFall", SoundManager::soundType::SFX, 8);
		SoundManager::Instance()->Load(SND_PIECEFALL, "PieceFall", SoundManager::soundType::SFX, 8);
		SoundManager::Instance()->Load(SND_GEMSFALLTITLE, "GemsFallTitle", SoundManager::soundType::SFX, 14);
		SoundManager::Instance()->Load(SND_BUTTONSELECT, "ButtonSelect", SoundManager::soundType::SFX, 8);

		_background = new Background({ -15, 0 });

		_gameStateMachine = new GameStateMachine();
		_gameStateMachine->PushState(new TitleScreenState());
		
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
	_isGameRunning = false;
}

void Game::Update(int deltaTime) {
	_background->Update(deltaTime);
	_gameStateMachine->Update(deltaTime);
}

void Game::Render() {

	SDL_RenderClear(_renderer);
	_background->Render();

	_gameStateMachine->Render();

	SDL_RenderPresent(_renderer);
}

void Game::Clean() {
	
	_background->Clean();

	TextureManager::Instance()->Clean();
	InputHandler::Instance()->Clean();

	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	TTF_Quit();
	SDL_Quit();

	delete _gameStateMachine;
	delete sGameInstance;
}