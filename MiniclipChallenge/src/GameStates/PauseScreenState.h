#pragma once

#include "GameState.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Buttons/Button.h"

#include <vector>

class PauseScreenState : public GameState {
public:
	static const int cPausedTextX;
	static const int cPausedTextY;
	static const char* cPausedString;

	static const int cFlavorTextX;
	static const int cFlavorTextY;
	static const char* cFlavorString;

	static const int cScoreTextX;
	static const int cScoreTextY;

	static const int cResumeButtonX;
	static const int cResumeButtonY;
	static const int cResumeContentX;
	static const int cResumeContentY;
	static const char* cResumeString;

	static const int cExitButtonX;
	static const int cExitButtonY;
	static const int cExitContentX;
	static const int cExitContentY;
	static const char* cExitString;

	void Init();
	void Update(int deltaTime);

private:

	Button* resumeButton_;
	Button* exitButton_;
};
