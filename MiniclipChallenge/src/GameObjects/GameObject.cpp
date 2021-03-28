#include "GameObject.h"

void GameObject::Init(Position pos) {
	_pos = pos;
}

Position GameObject::GetPos() {
	return _pos;
}