#pragma once

#include "GameState.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Buttons/Button.h"
#include "../GameObjects/Board.h"
#include "../GameObjects/ForegroundStrip.h"
#include "../GameObjects/EndLine.h"
#include "../Timer.h"
#include "../GameObjects/Clock.h"


#include <string>
#include <vector>

class PlayingState : public GameState {
public:
	static const Position cBoardPos;
	static const Position cEndLinePos;
	static const Position cEndTextPos;
	static const Position cClockPos;

	static const int cEndTextSpacing;

	void Init();
	void Update(int deltaTime);
	void Render();
	void Clean();

private:
	Board* board_;
	ForegroundStrip* foregroundStrip1_;
	ForegroundStrip* foregroundStrip2_;
	EndLine* endLine_;

	int displayedScore_;
	int displayedLevel_;
	int displayedFills_;
	GameObject* scoreValueText_;
	GameObject* levelValueText_;
	GameObject* fillsText_;

	Button* fillButton_;
	Button* pauseButton_;
	Button* pushButton_;
	Timer* pushButtonTimer_;

	Timer* columnTimer_;
	Clock* pushClock_;

	Timer* endGameTimer_;

	bool isGameLost_ = false;
};