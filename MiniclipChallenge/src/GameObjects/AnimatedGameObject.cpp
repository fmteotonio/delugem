#include "AnimatedGameObject.h"

#include "../Constants.h"
#include "../TextureManager.h"

void AnimatedGameObject::Init(Position pos, Dimensions dim, SDL_Texture* texture, std::string animationID, bool playNow) {
	GameObject::Init(pos);
	dim_ = dim;

	texture_ = texture;
	SetAnimation(animationID, playNow);
}

Dimensions AnimatedGameObject::GetDim() {
	return dim_;
}

void AnimatedGameObject::Update(int deltaTime) {
	currentAnimation_->Update(deltaTime);
}

void AnimatedGameObject::Render() { 
	SDL_Rect src;
	src.x = currentAnimation_->GetCurrentFrame() * dim_.w;
	src.y = currentAnimation_->GetFrameRow() * dim_.h;
	src.w = dim_.w;
	src.h = dim_.h;

	SDL_Rect dest;
	//Convert to Int before Scale to avoid sub-pixel movement
	dest.x = static_cast<int>(round(pos_.x)) * GAME_SCALE;
	dest.y = static_cast<int>(round(pos_.y)) * GAME_SCALE;
	dest.w = dim_.w * GAME_SCALE;
	dest.h = dim_.h * GAME_SCALE;
	TextureManager::Instance()->Draw(texture_, src, dest);
}

void AnimatedGameObject::Clean() { 
	for (auto animationPair : animations_) {
		delete animationPair.second;
	}
}

void AnimatedGameObject::AddAnimation(std::string id, Animation* animation) {
	animations_.insert({ id,animation });
}

void AnimatedGameObject::SetAnimation(std::string id, bool playNow) {
	currentAnimation_ = animations_.at(id);
	if (playNow)
		currentAnimation_->Play();
}