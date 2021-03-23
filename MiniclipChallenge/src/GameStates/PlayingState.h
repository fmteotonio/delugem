#pragma once

#include "GameState.h"
#include "../GameObjects/GameObject.h"

#include <string>
#include <vector>

class PlayingState : public GameState {
public:
	void Init();
	void Update(int deltaTime);
	void Render();
	void Clean();

	std::string stateID();
private:
	static const std::string stateID_;
	std::vector<GameObject*> gameObjects_;

	GameObject* scoreText_;
};
