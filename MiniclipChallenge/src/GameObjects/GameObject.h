#pragma once

#include<SDL_image.h>

class GameObject { 
public:  
	virtual void Init(float x, float y, int w, int h, SDL_Texture* texture, int frame, int frameRow);
	virtual void Update(int deltaTime);
	virtual void Render();
	virtual void Clean();
protected:  
	float x_;
	float y_;
	int w_;
	int h_;

	SDL_Texture* texture_;
	int frame_;
	int frameRow_;
};