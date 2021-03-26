#include "GameState.h"

std::string GameState::stateID() {
	return stateID_;
}

void GameState::Update(int deltaTime) {
	for (GameObject* gameObject : gameObjects_) {
		gameObject->Update(deltaTime);
	}
}

void GameState::Render() {
	for (GameObject* gameObject : gameObjects_) {
		gameObject->Render();
	}
}

void GameState::Clean() {
	for (GameObject* gameObject : gameObjects_) {
		gameObject->Clean();
		delete gameObject;
	}
}