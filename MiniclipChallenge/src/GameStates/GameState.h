#pragma once

#include<string>

class GameState {
public:
	virtual void Init() = 0;
	virtual void Update(int deltaTime) = 0;
	virtual void Render() = 0;  
	virtual void Clean() = 0;

	virtual std::string stateID() = 0;
private:

};