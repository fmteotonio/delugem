#pragma once

#include "GameState.h"

#include <vector>

class GameStateMachine {
public:
	void pushState(GameState* state);
	void changeState(GameState* state);
	void popState();

	void Update(int deltaTime);
	void Render();
	void Clean();

	bool IsEmpty();
private:
	std::vector<GameState*> gameStates_;
};