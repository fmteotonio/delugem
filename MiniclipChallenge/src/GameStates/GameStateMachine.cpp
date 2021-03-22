#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* state) {
	gameStates_.push_back(state);
	gameStates_.back()->Init();
}

void GameStateMachine::changeState(GameState* state) {
	if (!gameStates_.empty()) {
		if (gameStates_.back()->stateID() != state->stateID()){
			delete gameStates_.back();
			gameStates_.pop_back();
		}
		else return;
	}
	pushState(state);
}

void GameStateMachine::popState() {
	if (!gameStates_.empty()){
		gameStates_.back()->Clean();
		delete gameStates_.back();
		gameStates_.pop_back();
	}
}

void GameStateMachine::Update(int deltaTime) {
	if (!gameStates_.empty())
		gameStates_.back()->Update(deltaTime);
}

void GameStateMachine::Render() {
	if (!gameStates_.empty())
		gameStates_.back()->Render();
}

void GameStateMachine::Clean() {
	while (!gameStates_.empty()) {
		popState();
	}
}

bool GameStateMachine::IsEmpty() {
	return gameStates_.empty();
}