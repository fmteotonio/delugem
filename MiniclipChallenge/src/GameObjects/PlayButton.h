#pragma once

#include "GameObject.h"

class PlayButton : public GameObject {
public:
	enum class PlayButtonState {
		DEFAULT, PRESSED, GAMESTATE_TOPLAYING
	};

	PlayButton(float x, float y);

	void Update(int deltaTime);
	void HandleInput();
	void Render();
	void Clean();

	PlayButtonState playButtonState();
	bool TransitState(PlayButtonState newPlayButtonState);

private:
	PlayButtonState playButtonState_ = PlayButtonState::DEFAULT;

	Animation* defaultAnimation_;
	Animation* pressedAnimation_;

	GameObject* playText_;
};