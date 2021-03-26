#pragma once

#include "GameState.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Buttons/Button.h"

#include <vector>

class GameOverScreenState : public GameState {
public:
	void Init();
	void Update(int deltaTime);

private:

	Button* playAgainButton_;
	Button* exitButton_;
};
