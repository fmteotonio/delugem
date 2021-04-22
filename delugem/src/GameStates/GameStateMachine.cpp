#include "GameStateMachine.h"

#include "../TextureManager.h"

bool GameStateMachine::IsEmpty() {
	return _gameStates.empty();
}

void GameStateMachine::PushState(GameState* state) {
	_gameStates.push_back(state);
	_gameStates.back()->Init();
}

void GameStateMachine::ChangeState(GameState* state) {
	if (!_gameStates.empty()) {
		if (_gameStates.back()->GetStateID() != state->GetStateID()){
			_gameStates.back()->Clean();
			TextureManager::Instance()->ReleaseAll();
			delete _gameStates.back();
			_gameStates.pop_back();
		}
		else return;
	}
	PushState(state);
}

void GameStateMachine::PopState() {
	if (!_gameStates.empty()){
		_gameStates.back()->Clean();
		delete _gameStates.back();
		_gameStates.pop_back();
	}
}

void GameStateMachine::Update(int deltaTime) {
	if (!_gameStates.empty())
		_gameStates.back()->Update(deltaTime);
}

void GameStateMachine::Render() {
	if (!_gameStates.empty())
		_gameStates.back()->Render();
}

void GameStateMachine::Clean() {
	while (!_gameStates.empty()) {
		PopState();
	}
}