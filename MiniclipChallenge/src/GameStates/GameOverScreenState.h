#pragma once

#include "GameState.h"
#include "../GameObjects/Buttons/Button.h"

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
	static const char* cAgainString;
	static const char* cExitString;
	
	void Init();
	void Update(int deltaTime);

private:
	
	Button* _againButton;
	Button* _exitButton;
};
