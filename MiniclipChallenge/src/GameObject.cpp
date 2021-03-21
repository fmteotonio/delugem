#include "GameObject.h"

#include "Constants.h"
#include "TextureManager.h"

#include <iostream>

void GameObject::Init(float x, float y, int w, int h, SDL_Texture* texture, int frame, int frameRow) {
	x_ = x;
	y_ = y;
	w_ = w;
	h_ = h;

	texture_ = texture;
	frame_ = frame;
	frameRow_ = frameRow;
}

void GameObject::Update(int deltaTime) {

}

void GameObject::Render() { 
	SDL_Rect src;
	src.x = frame_ * w_;
	src.y = frameRow_ * h_;
	src.w = w_;
	src.h = h_;

	SDL_Rect dest;
	dest.x = (int)(x_ * GAME_SCALE);
	dest.y = (int)(y_ * GAME_SCALE);
	dest.w = w_ * GAME_SCALE;
	dest.h = h_ * GAME_SCALE;
	TextureManager::Draw(texture_, src, dest);
}

void GameObject::Clean() { 

}