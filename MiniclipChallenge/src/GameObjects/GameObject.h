#pragma once

#include<SDL_image.h>
#include<map>
#include<string>

#include "../Position.h"

class GameObject { 
public:
	virtual void Init(Position pos);
	virtual void Update(int deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;

	Position GetPos();

protected:
	Position pos_;
};