#include "Gem.h"

#include "../TextureManager.h"
#include "../Constants.h"

Gem::Gem(GemColor gemColor, float x, float y, int id) {
	gemColor_ = gemColor;
	id_ = id;

	SDL_Texture* objTexture = TextureManager::Instance()->LoadTexture(SPR_GEMS);
	
	int frameRow;
	switch (gemColor_) {
	case(GemColor::BEIGE):  frameRow = 0; break;
	case(GemColor::BLUE):   frameRow = 1; break;
	case(GemColor::GREEN):  frameRow = 2; break;
	case(GemColor::ORANGE): frameRow = 3; break;
	case(GemColor::PINK):   frameRow = 4; break;
	default: frameRow = 0;
	}

	//ANIMATION
	destroyAnimation_ = new Animation("Destroy", 0, 5, frameRow, 40);
	stillAnimation_ = new Animation("Still", 0, frameRow);

	GameObject::Init(x, y, GEM_W, GEM_H, objTexture, stillAnimation_);
}

int Gem::id() { return id_; }
Gem::GemColor Gem::gemColor()   { return gemColor_; }
Gem::GemStatus Gem::gemStatus() { return gemStatus_; }

void Gem::Move(float x, float y) {
	toMoveX_ += x;
	toMoveY_ += y;
}

void Gem::DestroyGem() {
	gemStatus_ = GemStatus::DESTROY_ANIMATION;
}

void Gem::Update(int deltaTime) {
	float moveUnitX = vx_ * (deltaTime / 1000.0f);
	float moveUnitY = vy_ * (deltaTime / 1000.0f);
	if (toMoveX_ != 0) {
		int sign = (toMoveX_ > 0) - (toMoveX_ < 0);
		if (toMoveX_ < moveUnitX && toMoveX_ > -moveUnitX) {
			x_ += toMoveX_;
			toMoveX_ -= toMoveX_;
			vx_ = 0;
		}
		else {
			x_ += moveUnitX * sign;
			toMoveX_ -= moveUnitX * sign;

			vx_ += a_ * (deltaTime / 1000.0f);
		}
	}
	if (toMoveY_ != 0) {
		int sign = (toMoveY_ > 0) - (toMoveY_ < 0);
		if (toMoveY_ < moveUnitY && toMoveY_ > -moveUnitY) {
			y_ += toMoveY_;
			toMoveY_ -= toMoveY_;
			vy_ = 0;
		}
		else {
			y_ += moveUnitY * sign;
			toMoveY_ -= moveUnitY * sign;
			vy_ += a_ * (deltaTime / 1000.0f);
		}
	}

	GameObject::Update(deltaTime);
}

void Gem::Render() {
	if (animation_->id() == stillAnimation_->id() && gemStatus_ == GemStatus::DESTROY_ANIMATION) {
		animation_ = destroyAnimation_;
		animation_->Play();
	}
	if (animation_->id() == destroyAnimation_->id() && animation_->PlayedOnce()) {
		gemStatus_ = GemStatus::TO_DESTROY;
		return;
	}

	GameObject::Render();
}

void Gem::Clean() {
	delete stillAnimation_;
	delete destroyAnimation_;

	GameObject::Clean();
}