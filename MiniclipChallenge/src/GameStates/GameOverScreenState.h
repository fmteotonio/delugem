#pragma once

#include "GameState.h"
#include "../Constants.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Buttons/Button.h"

#include <vector>

class GameOverScreenState : public GameState {
public:
	static const Position cUpperStripPos;
	static const Position cLowerStripPos;

	static const Position cGameOverTextPos;
	static const Position cFlavorTextPos;
	static const Position cScoreTextPos;

	static const Position cAgainButtonPos;
	static const Position cExitButtonPos;
	static const Position cAgainContentPos;
	static const Position cExitContentPos;

	static const char* cGameOverString;

	static const char* cFlavorString;


	static const float cAgainButtonX;
	static const float cAgainButtonY;
	static const float cAgainContentX;
	static const float cAgainContentY;
	static const char* cAgainString;

	static const float cExitButtonX;
	static const float cExitButtonY;
	static const float cExitContentX;
	static const float cExitContentY;
	static const char* cExitString;

	void Init();
	void Update(int deltaTime);

private:
	
	Button* againButton_;
	Button* exitButton_;
};
