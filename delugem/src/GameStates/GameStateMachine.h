#pragma once

#include "GameState.h"

#include <vector>

class GameStateMachine {
public:

	bool IsEmpty();

	void PushState(GameState* state);
	void ChangeState(GameState* state);
	void PopState();

	void Update(int deltaTime);
	void Render();
	void Clean();

private:

	std::vector<GameState*> _gameStates;

};