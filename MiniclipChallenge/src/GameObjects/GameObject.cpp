#include "GameObject.h"

#include "../Constants.h"
#include "../TextureManager.h"

void GameObject::Init(float x, float y) {
	x_ = x;
	y_ = y;
}

float GameObject::GetX() {
	return x_;
}

float GameObject::GetY() {
	return y_;
}