#pragma once

#include "GameState.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Buttons/Button.h"
#include "../GameObjects/Board.h"
#include "../GameObjects/ForegroundStrip.h"
#include "../Timer.h"
#include "../GameObjects/Clock.h"

class PlayingState : public GameState {
public:
	static const Position cUpperStripPos;
	static const Position cLowerStripPos;

	static const Position cBoardPos;
	static const Position cEndLinePos;
	static const Position cEndTextPos;
	static const Position cClockPos;

	static const int cEndTextSpacing;

	static const int cTopTextY;
	static const int cBotTextY;
	static const int cTopButtonY;
	static const int cBotButtonY;

	static const Position cLevelTextPos;
	static const Position cScoreTextPos;
	static const Position cPushTextPos;
	static const Position cFillsTextPos;
	static const Position cFillsText2Pos;

	static const Position cLevelValuePos;
	static const Position cScoreValuePos;
	static const Position cFillsValuePos;

	static const Position cPauseButtonPos;
	static const Position cFillsButtonPos;
	static const Position cPushButtonPos;

	static const Position cPauseContentPos;
	static const Position cFillsContentPos;
	static const Position cPushContentPos;

	static const char* cFillIconPath;
	static const char* cPauseIconPath;
	static const char* cPushIconPath;

	void Init();
	void Update(int deltaTime);
	void Render();
	void Clean();

private:
	Timer* columnTimer_;
	Timer* pushButtonTimer_;
	Timer* endGameTimer_;

	Board* board_;
	GameObject* endLine_;
	ForegroundStrip* foregroundStrip1_;
	ForegroundStrip* foregroundStrip2_;
	Clock* pushClock_;

	Button* fillButton_;
	Button* pauseButton_;
	Button* pushButton_;

	int displayedScore_;
	int displayedLevel_;
	int displayedFills_;
	GameObject* scoreValueText_;
	GameObject* levelValueText_;
	GameObject* fillsText_;
	
	void InitUI();
};