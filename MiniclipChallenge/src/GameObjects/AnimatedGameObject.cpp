#include "AnimatedGameObject.h"

#include "../Constants.h"
#include "../TextureManager.h"

void AnimatedGameObject::Init(Position pos, Dimensions dim, SDL_Texture* texture, std::string animationID, bool playNow) {
	GameObject::Init(pos);
	_dim = dim;

	_texture = texture;
	SetAnimation(animationID, playNow);
}

Dimensions AnimatedGameObject::GetDim() {
	return _dim;
}

void AnimatedGameObject::Update(int deltaTime) {
	_currentAnimation->Update(deltaTime);
}

void AnimatedGameObject::Render() { 
	SDL_Rect src;
	src.x = _currentAnimation->GetCurrentFrame() * _dim.w;
	src.y = _currentAnimation->GetFrameRow() * _dim.h;
	src.w = _dim.w;
	src.h = _dim.h;

	SDL_Rect dest;
	//Convert to Int before Scale to avoid sub-pixel movement
	dest.x = static_cast<int>(round(_pos.x)) * GAME_SCALE;
	dest.y = static_cast<int>(round(_pos.y)) * GAME_SCALE;
	dest.w = _dim.w * GAME_SCALE;
	dest.h = _dim.h * GAME_SCALE;
	TextureManager::Instance()->Draw(_texture, src, dest);
}

void AnimatedGameObject::Clean() { 
	for (auto animationPair : _animations) {
		delete animationPair.second;
	}
}

void AnimatedGameObject::AddAnimation(std::string id, Animation* animation) {
	_animations.insert({ id,animation });
}

void AnimatedGameObject::SetAnimation(std::string id, bool playNow) {
	_currentAnimation = _animations.at(id);
	if (playNow)
		_currentAnimation->Play();
}