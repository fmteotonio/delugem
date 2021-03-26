#include "Game.h"
#include "Constants.h"

int main(int argc, char *argv[])
{
	const int frameDelay = 1000 / TARGET_FPS;

	Uint32 frameStart = SDL_GetTicks();
	Uint32 lastFrameStart = SDL_GetTicks();
	int frameTime;
	
	if (Game::Instance()->Init("Delugem", SCREEN_W * GAME_SCALE, SCREEN_H * GAME_SCALE, false)) {
		while (Game::Instance()->IsGameRunning()) {
			frameStart = SDL_GetTicks();

			int deltaTime = frameStart - lastFrameStart;

			Game::Instance()->HandleEvents();
			Game::Instance()->Update(deltaTime);
			Game::Instance()->Render();

			frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime) 
				SDL_Delay(frameDelay - frameTime);
			lastFrameStart = frameStart;
		}

		Game::Instance()->Clean();
		return 0;
	}
	else
		return 1;
}