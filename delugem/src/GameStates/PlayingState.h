#pragma once

#include "GameState.h"
#include "../Timer.h"
#include "../gameObjects/Board.h"
#include "../gameObjects/Clock.h"
#include "../gameObjects/GameObject.h"
#include "../gameObjects/Background.h"
#include "../gameObjects/ForegroundStrip.h"
#include "../gameObjects/buttons/Button.h"

class PlayingState : public GameState {
public:

	static const Position cUpperStripPos;
	static const Position cLowerStripPos;

	static const Position cBoardPos;
	static const int cBoardColumns;

	static const Position cEndLinePos;
	static const Position cEndTextPos;
	static const char* cEndTextString;
	static const int cEndTextSpacing;

	static const Position cClockPos;

	static const int cTopTextY;
	static const int cBotTextY;
	static const int cTopButtonY;
	static const int cBotButtonY;

	static const Position cLevelTextPos;
	static const Position cScoreTextPos;
	static const Position cScoreText2Pos;
	static const Position cPushTextPos;
	static const Position cFillsTextPos;
	static const Position cFillsText2Pos;

	static const Position cLevelValuePos;
	static const Position cScoreValuePos;
	static const Position cScoreValue2Pos;
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

	static const int cEndGameTimerValue;
	static const int cPushButtonTimerValue;

	static const char* cID;

	void Init();
	void Update(int deltaTime);
	void Render();
	void Clean();

private:

	Timer* _columnTimer;
	Timer* _pushButtonTimer;
	Timer* _endGameTimer;

	Board* _board;
	GameObject* _endLine;
	Background* _background;
	ForegroundStrip* _foregroundStrip1;
	ForegroundStrip* _foregroundStrip2;
	Clock* _pushClock;

	Button* _fillButton;
	Button* _pauseButton;
	Button* _pushButton;

	int _displayedScore;
	int _displayedLevel;
	int _displayedFills;
	int _displayedNextLevelScore;
	GameObject* _scoreValueText;
	GameObject* _levelValueText;
	GameObject* _fillsText;
	GameObject* _scoreValue2Text;

	void InitUI();
	void CheckScore();
	void CheckLevel();
	void CheckFills();
	void CheckButtons();
	void CheckGameOver();
};