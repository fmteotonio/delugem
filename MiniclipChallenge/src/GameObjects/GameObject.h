#pragma once

#include<SDL_image.h>
#include<map>
#include<string>

#include "../Animation.h"

class GameObject { 
public:
	virtual void Init(float x, float y);
	virtual void Update(int deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;

protected:
	float x_;
	float y_;
};