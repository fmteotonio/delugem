#pragma once

#include "GameState.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Buttons/Button.h"

#include <vector>

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
	static const char* cResumeString;
	static const char* cExitString;

	void Init();
	void Update(int deltaTime);

private:

	Button* resumeButton_;
	Button* exitButton_;
};
