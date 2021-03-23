#pragma once

#include "GameObject.h"

class PlayButton : public GameObject {
public:
	enum class PlayButtonState {
		DEFAULT, PRESSED
	};

	PlayButton(float x, float y);

	bool clicked();

	void Update(int deltaTime);
	void HandleInput();
	void Render();
	void Clean();

private:
	PlayButtonState playButtonState = PlayButtonState::DEFAULT;

	Animation* defaultAnimation;
	Animation* pressedAnimation;


	GameObject* playText_;
	bool clicked_ = false;
};