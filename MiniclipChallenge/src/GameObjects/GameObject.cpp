#include "GameObject.h"

#include "../Constants.h"
#include "../TextureManager.h"

#include <iostream>

void GameObject::Init(float x, float y, int w, int h, SDL_Texture* texture, Animation* animation) {
	x_ = x;
	y_ = y;
	w_ = w;
	h_ = h;
	texture_ = texture;
	animation_ = animation;
}

void GameObject::Update(int deltaTime) {
	animation_->Update(deltaTime);
}

void GameObject::Render() { 
	SDL_Rect src;
	src.x = animation_->getCurrentFrame() * w_;
	src.y = animation_->frameRow() * h_;
	src.w = w_;
	src.h = h_;

	SDL_Rect dest;
	//Convert to Int before Scale to avoid sub-pixel movement
	dest.x = int(round(x_)) * GAME_SCALE;
	dest.y = int(round(y_)) * GAME_SCALE; 
	dest.w = w_ * GAME_SCALE;
	dest.h = h_ * GAME_SCALE;
	TextureManager::Instance()->Draw(texture_, src, dest);
}

void GameObject::Clean() { 
	delete animation_;
}