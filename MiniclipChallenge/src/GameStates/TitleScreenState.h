#pragma once

#include "GameState.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Button.h"

#include <vector>

class TitleScreenState : public GameState {
public:
	void Init();
	void Update(int deltaTime);

private:

	Button* playButton_;
};
