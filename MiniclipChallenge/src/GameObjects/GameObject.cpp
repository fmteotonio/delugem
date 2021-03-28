#include "GameObject.h"

#include "../Constants.h"
#include "../TextureManager.h"

void GameObject::Init(Position pos) {
	pos_ = pos;
}

Position GameObject::GetPos() {
	return pos_;
}