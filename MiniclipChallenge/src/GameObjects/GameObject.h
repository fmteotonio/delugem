#pragma once

#include<SDL_image.h>

#include "../Animation.h"

class GameObject { 
public:  
	virtual void Init(float x, float y, int w, int h, SDL_Texture* texture, Animation* animation);
	virtual void Update(int deltaTime);
	virtual void Render();
	virtual void Clean();
protected:
	float x_;
	float y_;
	int w_;
	int h_;

	SDL_Texture* texture_;
	Animation* animation_;
};