#pragma once

#include<map>
#include<string>

#include<SDL_image.h>

#include "GameObject.h"
#include "../Animation.h"
#include "../structs/Dimensions.h"

class AnimatedGameObject : public GameObject { 
public:  

	virtual void Init(Position pos, Dimensions dim, SDL_Texture* texture, std::string animationID, bool playNow);
	virtual void Init(Position pos, Dimensions srcDim, Dimensions destDim, SDL_Texture* texture, std::string animationID, bool playNow);

	Dimensions GetDim();

	void AddAnimation(std::string id, Animation* animation);
	void SetAnimation(std::string id, bool playNow);

	virtual void Update(int deltaTime);
	virtual void Render();
	virtual void Clean();

protected:

	Dimensions _srcDim;
	Dimensions _destDim;

	SDL_Texture* _texture;
	Animation* _currentAnimation;
	std::map<std::string, Animation*> _animations;

};