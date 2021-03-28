#pragma once

#include<map>
#include<string>

#include<SDL_image.h>

#include "GameObject.h"
#include "../Animation.h"
#include "../Dimensions.h"

class AnimatedGameObject : public GameObject { 
public:  
	virtual void Init(Position pos, Dimensions dim, SDL_Texture* texture, std::string animationID, bool playNow);
	virtual void Update(int deltaTime);
	virtual void Render();
	virtual void Clean();

	Dimensions GetDim();

	void AddAnimation(std::string id, Animation* animation);
	void SetAnimation(std::string id, bool playNow);
protected:
	Dimensions dim_;

	SDL_Texture* texture_;
	Animation* currentAnimation_;
	std::map<std::string, Animation*> animations_;
};