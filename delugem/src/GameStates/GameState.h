#pragma once

#include<string>
#include<vector>

#include "../gameObjects/GameObject.h"

class GameState {
public:
	virtual void Init() = 0;
	virtual void Update(int deltaTime);
	virtual void Render();  
	virtual void Clean();

	virtual std::string GetStateID();
protected:
	std::string stateID_;

	std::vector<GameObject*> _gameObjects;
};