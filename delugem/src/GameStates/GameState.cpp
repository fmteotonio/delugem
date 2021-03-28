#include "GameState.h"

std::string GameState::GetStateID() {
	return stateID_;
}

void GameState::Update(int deltaTime) {
	for (GameObject* gameObject : _gameObjects) {
		gameObject->Update(deltaTime);
	}
}

void GameState::Render() {
	for (GameObject* gameObject : _gameObjects) {
		gameObject->Render();
	}
}

void GameState::Clean() {
	for (GameObject* gameObject : _gameObjects) {
		gameObject->Clean();
		delete gameObject;
	}
}