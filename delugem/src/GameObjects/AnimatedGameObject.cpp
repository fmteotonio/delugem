#include "AnimatedGameObject.h"

#include "../Constants.h"
#include "../TextureManager.h"

void AnimatedGameObject::Init(Position pos, Dimensions dim, SDL_Texture* texture, std::string animationID, bool playNow) {
	_srcDim = dim;
	_destDim = dim;
	_texture = texture;

	SetAnimation(animationID, playNow);

	GameObject::Init(pos);
}

void AnimatedGameObject::Init(Position pos, Dimensions srcDim, Dimensions destDim, SDL_Texture* texture, std::string animationID, bool playNow) {
	_srcDim = srcDim;
	_destDim = destDim;
	_texture = texture;

	SetAnimation(animationID, playNow);

	GameObject::Init(pos);
}

Dimensions AnimatedGameObject::GetDim() {
	return _destDim;
}

void AnimatedGameObject::AddAnimation(std::string id, Animation* animation) {
	_animations.insert({ id,animation });
}

void AnimatedGameObject::SetAnimation(std::string id, bool playNow) {
	_currentAnimation = _animations.at(id);
	if (playNow)
		_currentAnimation->Play();
}

void AnimatedGameObject::Update(int deltaTime) {
	_currentAnimation->Update(deltaTime);
}

void AnimatedGameObject::Render() { 
	SDL_Rect src;
	src.x = _currentAnimation->GetCurrentFrame() * _srcDim.w;
	src.y = _currentAnimation->GetFrameRow() * _srcDim.h;
	src.w = _srcDim.w;
	src.h = _srcDim.h;

	SDL_Rect dest;
	//Round to Int before Scale to avoid sub-pixel movement
	dest.x = static_cast<int>(round(_pos.x)) * GAME_SCALE;
	dest.y = static_cast<int>(round(_pos.y)) * GAME_SCALE;
	dest.w = _destDim.w * GAME_SCALE;
	dest.h = _destDim.h * GAME_SCALE;
	TextureManager::Instance()->Draw(_texture, src, dest);
}

void AnimatedGameObject::Clean() { 
	for (std::pair<std::string, Animation*> animationPair : _animations) {
		delete animationPair.second;
	}
}