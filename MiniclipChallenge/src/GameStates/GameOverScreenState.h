#pragma once

#include "GameState.h"
#include "../Constants.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Buttons/Button.h"

#include <vector>

class GameOverScreenState : public GameState {
public:
	static const int cGameOverTextX;
	static const int cGameOverTextY;
	static const char* cGameOverString;

	static const int cFlavorTextX;
	static const int cFlavorTextY;
	static const char* cFlavorString;

	static const int cScoreTextX;
	static const int cScoreTextY;

	static const int cAgainButtonX;
	static const int cAgainButtonY;
	static const int cAgainContentX;
	static const int cAgainContentY;
	static const char* cAgainString;

	static const int cExitButtonX;
	static const int cExitButtonY;
	static const int cExitContentX;
	static const int cExitContentY;
	static const char* cExitString;

	void Init();
	void Update(int deltaTime);

private:
	
	Button* againButton_;
	Button* exitButton_;
};
