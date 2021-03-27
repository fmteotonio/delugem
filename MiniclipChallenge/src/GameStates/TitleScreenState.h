#pragma once

#include "GameState.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Buttons/Button.h"
#include "../GameObjects/Board.h"

#include <vector>

class TitleScreenState : public GameState {
public:
	void Init();
	void Update(int deltaTime);
private:
	static const int cStartButtonX;
	static const int cStartButtonY;

	Button* playButton_;
	Button* howButton_;

	Board* board1_;
	Board* board2_;
	
	bool hasPlayedSound_ = false;

	void SetupTitleAnimation();
};