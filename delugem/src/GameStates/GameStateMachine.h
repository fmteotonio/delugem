#pragma once

#include "GameState.h"

#include <vector>

class GameStateMachine {
public:
	void PushState(GameState* state);
	void ChangeState(GameState* state);
	void PopState();

	void Update(int deltaTime);
	void Render();
	void Clean();

	bool IsEmpty();
private:
	std::vector<GameState*> _gameStates;
};