#include "AnimatedGameObject.h"

#include "../Constants.h"
#include "../TextureManager.h"

void AnimatedGameObject::Init(float x, float y, int w, int h, SDL_Texture* texture, std::string animationID, bool playNow) {
	GameObject::Init(x, y);
	w_ = w;
	h_ = h;
	texture_ = texture;
	setAnimation(animationID, playNow);
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
	dest.x = int(round(x_)) * GAME_SCALE;
	dest.y = int(round(y_)) * GAME_SCALE; 
	dest.w = w_ * GAME_SCALE;
	dest.h = h_ * GAME_SCALE;
	TextureManager::Instance()->Draw(texture_, src, dest);
}

void AnimatedGameObject::Clean() { 
	for (auto animationPair : animations_) {
		delete animationPair.second;
	}
}

void AnimatedGameObject::addAnimation(std::string id, Animation* animation) {
	animations_.insert({ id,animation });
}

void AnimatedGameObject::setAnimation(std::string id, bool playNow) {
	currentAnimation_ = animations_.at(id);
	if (playNow)
		currentAnimation_->Play();
}