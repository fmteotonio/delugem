#include "GameStateMachine.h"

#include "../TextureManager.h"

void GameStateMachine::PushState(GameState* state) {
	gameStates_.push_back(state);
	gameStates_.back()->Init();
}

void GameStateMachine::ChangeState(GameState* state) {
	if (!gameStates_.empty()) {
		if (gameStates_.back()->GetStateID() != state->GetStateID()){
			delete gameStates_.back();
			gameStates_.pop_back();
		}
		else return;
	}
	PushState(state);
}

void GameStateMachine::PopState() {
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
		PopState();
	}
}

bool GameStateMachine::IsEmpty() {
	return gameStates_.empty();
}