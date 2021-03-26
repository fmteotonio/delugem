#pragma once

#include "GameState.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Buttons/Button.h"

#include <vector>

class PauseScreenState : public GameState {
public:
	void Init();
	void Update(int deltaTime);

private:

	Button* resumeButton_;
	Button* exitButton_;
};
