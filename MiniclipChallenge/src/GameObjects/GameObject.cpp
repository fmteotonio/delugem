#include "GameObject.h"

void GameObject::Init(Position pos) {
	pos_ = pos;
}

Position GameObject::GetPos() {
	return pos_;
}