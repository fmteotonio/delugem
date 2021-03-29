#pragma once

#include "GameState.h"
#include "../gameObjects/buttons/Button.h"

class PauseScreenState : public GameState {
public:
	static const Position cUpperStripPos;
	static const Position cLowerStripPos;

	static const Position cPausedTextPos;
	static const Position cFlavorTextPos;
	static const Position cScoreTextPos;

	static const Position cResumeButtonPos;
	static const Position cExitButtonPos;
	static const Position cResumeContentPos;
	static const Position cExitContentPos;

	static const char* cPausedString;
	static const char* cFlavorString;
	static const char* cScorePartialString;
	static const char* cResumeString;
	static const char* cExitString;

	void Init();
	void Update(int deltaTime);

private:

	Button* _resumeButton;
	Button* _exitButton;

};