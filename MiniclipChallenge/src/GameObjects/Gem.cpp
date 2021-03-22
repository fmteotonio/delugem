#include "Gem.h"

#include "../TextureManager.h"
#include "../Constants.h"

Gem::Gem(GemColor gemColor, float x, float y, int boardX,      int boardY,      int id) :
	     gemColor_(gemColor),                 boardX_(boardX), boardY_(boardY), id_(id){

	SDL_Texture* objTexture = nullptr;

	switch (gemColor_) {
	case(GemColor::BEIGE):  objTexture = TextureManager::Instance()->LoadTexture(SPR_BEIGEGEM);  break;
	case(GemColor::BLUE):   objTexture = TextureManager::Instance()->LoadTexture(SPR_BLUEGEM);   break;
	case(GemColor::GREEN):  objTexture = TextureManager::Instance()->LoadTexture(SPR_GREENGEM);  break;
	case(GemColor::ORANGE): objTexture = TextureManager::Instance()->LoadTexture(SPR_ORANGEGEM); break;
	case(GemColor::PINK):   objTexture = TextureManager::Instance()->LoadTexture(SPR_PINKGEM);   break;
	}

	//ANIMATION
	destroyAnimation = new Animation("Destroy", 0, 7, 0, 40);
	stillAnimation = new Animation("Still", 0, 0);

	gemStatus_ = GemStatus::DEFAULT;
	//destroyAnimationStarted_ = false;
	//destroyAnimationSpeed_ = 40;
	//destroyAnimationFrameNumber_ = 8;
	//destroyAnimationStartTime_ = 0;

	GameObject::Init(x, y, GEM_W, GEM_H, objTexture, stillAnimation);
}

int Gem::id()			      { return id_; }
Gem::GemColor Gem::gemColor() { return gemColor_; }
Gem::GemStatus Gem::gemStatus() { return gemStatus_; }

void Gem::Update(int deltaTime) {
}

void Gem::Render() {
	if (animation_->id() == stillAnimation->id() && gemStatus_ == GemStatus::DESTROY_ANIMATION) {
		animation_ = destroyAnimation;
		animation_->Play();
	}
	if (animation_->id() == destroyAnimation->id() && animation_->PlayedOnce()) {
		gemStatus_ = GemStatus::TO_DESTROY;
		return;
	}
	GameObject::Render();
}

void Gem::Move(float x, float y) {
	x_ += x;
	y_ += y;
}

void Gem::MoveB(int boardX, int boardY) {
	boardX_ += boardX;
	boardY_ += boardY;
}

void Gem::DestroyGem() {
	gemStatus_ = GemStatus::DESTROY_ANIMATION;
}