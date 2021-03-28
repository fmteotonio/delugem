#include "AnimatedGameObject.h"

#include "../Constants.h"
#include "../TextureManager.h"

void AnimatedGameObject::Init(Position pos, int w, int h, SDL_Texture* texture, std::string animationID, bool playNow) {
	GameObject::Init(pos);
	w_ = w;
	h_ = h;
	texture_ = texture;
	SetAnimation(animationID, playNow);
}

void AnimatedGameObject::Update(int deltaTime) {
	currentAnimation_->Update(deltaTime);
}

void AnimatedGameObject::Render() { 
	SDL_Rect src;
	src.x = currentAnimation_->GetCurrentFrame() * w_;
	src.y = currentAnimation_->GetFrameRow() * h_;
	src.w = w_;
	src.h = h_;

	SDL_Rect dest;
	//Convert to Int before Scale to avoid sub-pixel movement
	dest.x = static_cast<int>(round(pos_.x)) * GAME_SCALE;
	dest.y = static_cast<int>(round(pos_.y)) * GAME_SCALE;
	dest.w = w_ * GAME_SCALE;
	dest.h = h_ * GAME_SCALE;
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