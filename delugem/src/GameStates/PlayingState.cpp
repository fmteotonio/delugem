#include "PlayingState.h"

#include "../gameObjects/EndLine.h"
#include "../gameObjects/ForegroundStrip.h"
#include "../gameObjects/Background.h"
#include "../gameObjects/Board.h"
#include "../gameObjects/Clock.h"
#include "../gameObjects/buttons/SmallButton.h"
#include "../gameObjects/texts/ShadowedText.h"
#include "../gameObjects/texts/VerticalShadowedText.h"
#include "../gameObjects/staticImages/SmallIcon.h"
#include "../gameStates/PauseScreenState.h"
#include "../gameStates/GameOverScreenState.h"
#include "../Constants.h"
#include "../GameManager.h"
#include "../SoundManager.h"
#include "../Game.h"

#include <iostream>

//..........................GameObject Constants........................

const Position PlayingState::cUpperStripPos = { 0,  0 };
const Position PlayingState::cLowerStripPos = { 0, SCREEN_H - ForegroundStrip::cDestDim.h };

const Position PlayingState::cBoardPos = { SCREEN_W , 28 + Gem::cDim.h * (10 - cBoardColumns) };
const int      PlayingState::cBoardColumns = 10;

const Position PlayingState::cEndLinePos     = { GameManager::cEndGemsMargin * Gem::cDim.w , 28 };
const Position PlayingState::cEndTextPos     = { std::round(PlayingState::cEndLinePos.x / 1.1) , 67 };
const char*	   PlayingState::cEndTextString  = "END ZONE";
const int      PlayingState::cEndTextSpacing = -4;

const Position PlayingState::cClockPos     = { 290, 193 };

//........................UI GameObject Constants........................

const int PlayingState::cTopTextY   = 14;
const int PlayingState::cBotTextY   = 202;
const int PlayingState::cTopButtonY = cTopTextY - 12;
const int PlayingState::cBotButtonY = cBotTextY - 12;

const Position PlayingState::cLevelTextPos  = { 7,  cTopTextY };
const Position PlayingState::cScoreTextPos  = { 165,  cTopTextY };
const Position PlayingState::cScoreText2Pos = { cScoreTextPos.x + 117, cTopTextY };
const Position PlayingState::cPushTextPos   = { 313,  cBotTextY };
const Position PlayingState::cFillsTextPos  = { 7,  cBotTextY };
const Position PlayingState::cFillsText2Pos = { cFillsTextPos.x + 50, cBotTextY };

const Position PlayingState::cLevelValuePos = { cLevelTextPos.x + 71 , cTopTextY };
const Position PlayingState::cScoreValuePos = { cScoreTextPos.x + 99 , cTopTextY };
const Position PlayingState::cScoreValue2Pos = { cScoreTextPos.x + 173, cScoreValuePos.y };
const Position PlayingState::cFillsValuePos = { cFillsTextPos.x + 38 , cBotTextY };

const Position PlayingState::cPauseButtonPos = { 351 , cTopButtonY };
const Position PlayingState::cFillsButtonPos = { cFillsTextPos.x + 91, cBotButtonY };
const Position PlayingState::cPushButtonPos  = { cPushTextPos.x + 38 , cBotButtonY };

const Position PlayingState::cPauseContentPos = { cPauseButtonPos.x + 8 , cPauseButtonPos.y + 8 };
const Position PlayingState::cFillsContentPos = { cFillsButtonPos.x + 8, cFillsButtonPos.y + 8 };
const Position PlayingState::cPushContentPos  = { cPushButtonPos.x + 8 , cPushButtonPos.y + 8 };

const char* PlayingState::cFillIconPath  = "res/images/iconfill.png";
const char* PlayingState::cPauseIconPath = "res/images/iconpause.png";
const char* PlayingState::cPushIconPath  = "res/images/iconpush.png";

//........................Timer Constants........................

const int PlayingState::cEndGameTimerValue = 500;
const int PlayingState::cPushButtonTimerValue = 100;

//........................................................................

const char* PlayingState::cID = "PLAYING";

void PlayingState::Init() {

	stateID_ = cID;

	SoundManager::Instance()->PlayMusic(SoundManager::cGameMusic, -1);

	/*
	columnTimer:	 Time between columns being pushed into the board;
	pushButtonTimer: Small delay to avoid repeated pushes;
	endGameTimer:	 Small delay to game over transition;
	*/
	_columnTimer = new Timer(GameManager::Instance()->GetTimePerColumn(), true);
	_pushButtonTimer = new Timer(-1, true);
	_endGameTimer = new Timer(cEndGameTimerValue, false);

	GameManager::Instance()->ResetGame();

	//Background

	_gameObjects.push_back(_background = new Background());

	//Board & End Zone

	_gameObjects.push_back(_board = new Board(cBoardPos, cBoardColumns, true));
	_board->PushColumns(GameManager::Instance()->cStartColumns);

	_gameObjects.push_back(_endLine = new EndLine(cEndLinePos));
	_gameObjects.push_back(new VerticalShadowedText(cEndTextPos, Text::Align::MID, FNT_M3X6, FNT_SMALL, cEndTextSpacing, cEndTextString, WHITE, BLACK));

	//Foreground Strips & Visual Clock

	_gameObjects.push_back(_foregroundStrip1 = new ForegroundStrip(cUpperStripPos));
	_gameObjects.push_back(_foregroundStrip2 = new ForegroundStrip(cLowerStripPos));
	_gameObjects.push_back(_pushClock = new Clock(cClockPos, _columnTimer));
	
	//All Text and Buttons
	InitUI();
}



void PlayingState::Update(int deltaTime) {

	GameState::Update(deltaTime);
	
	_endGameTimer->Update(deltaTime);
	
	_pushButtonTimer->Update(deltaTime);
	_pushClock->UpdateFrame();

	//Check for column pushes.
	_columnTimer->Update(deltaTime);
	if (_columnTimer->HasEnded()) {
		_board->PushColumns(1);
		_pushButtonTimer->ResetTimer(cPushButtonTimerValue);
		_columnTimer->ResetTimer(GameManager::Instance()->GetTimePerColumn());
	}

	CheckScore();
	CheckLevel();
	CheckFills();
	CheckButtons();
	CheckGameOver();

}

void PlayingState::Render() {
	GameState::Render();

	_scoreValueText->Render();
	_levelValueText->Render();
	_fillsText->Render();
	_scoreValue2Text->Render();
}

void PlayingState::Clean() {

	GameState::Clean();

	_scoreValueText->Clean();
	_levelValueText->Clean();
	_fillsText->Clean();
	_scoreValue2Text->Clean();
	delete _scoreValueText;
	delete _levelValueText;
	delete _fillsText;
	delete _scoreValue2Text;

	delete _pushButtonTimer;
	delete _columnTimer;
	delete _endGameTimer;
}

/* Create all text, button and button content objects. */
void PlayingState::InitUI() {

	//Static text elements

	_gameObjects.push_back(new ShadowedText(cScoreTextPos, Text::Align::MIDLEFT, FNT_M6X11, FNT_SMALL, "SCORE:", WHITE, BLACK));
	_gameObjects.push_back(new ShadowedText(cLevelTextPos, Text::Align::MIDLEFT, FNT_M6X11, FNT_SMALL, "LEVEL:", WHITE, BLACK));
	_gameObjects.push_back(new ShadowedText(cPushTextPos, Text::Align::MIDLEFT, FNT_M6X11, FNT_SMALL, "PUSH", WHITE, BLACK));
	_gameObjects.push_back(new ShadowedText(cFillsTextPos, Text::Align::MIDLEFT, FNT_M6X11, FNT_SMALL, "FILL (", WHITE, BLACK));
	_gameObjects.push_back(new ShadowedText(cFillsText2Pos, Text::Align::MIDLEFT, FNT_M6X11, FNT_SMALL, "left)", WHITE, BLACK));
	_gameObjects.push_back(new ShadowedText(cScoreText2Pos, Text::Align::MIDRIGHT, FNT_M6X11, FNT_SMALL, " / ", WHITE, BLACK));

	//Buttons

	_gameObjects.push_back(_fillButton = new SmallButton(cFillsButtonPos));
	_gameObjects.push_back(_pauseButton = new SmallButton(cPauseButtonPos));
	_gameObjects.push_back(_pushButton = new SmallButton(cPushButtonPos));

	//Button Icons

	_pauseButton->AddContent(new SmallIcon(cPauseContentPos, cPauseIconPath));
	_pushButton->AddContent(new SmallIcon(cPushContentPos, cPushIconPath));
	_fillButton->AddContent(new SmallIcon(cFillsContentPos, cFillIconPath));

	//Dynamic text elements

	_displayedScore = GameManager::Instance()->GetScore();
	_displayedLevel = GameManager::Instance()->GetLevel();
	_displayedFills = GameManager::Instance()->GetFillsLeft();
	_displayedNextLevelScore = GameManager::Instance()->GetScoreToNextLevel();

	_scoreValueText = new ShadowedText(cScoreValuePos, Text::Align::MIDRIGHT, FNT_M6X11, FNT_SMALL, std::to_string(_displayedScore), WHITE, BLACK);
	_levelValueText = new ShadowedText(cLevelValuePos, Text::Align::MIDRIGHT, FNT_M6X11, FNT_SMALL, std::to_string(_displayedLevel), WHITE, BLACK);
	_fillsText = new ShadowedText(cFillsValuePos, Text::Align::MIDLEFT, FNT_M6X11, FNT_SMALL, std::to_string(_displayedFills), WHITE, BLACK);
	_scoreValue2Text = new ShadowedText(cScoreValue2Pos, Text::Align::MIDRIGHT, FNT_M6X11, FNT_SMALL, std::to_string(_displayedNextLevelScore), WHITE, BLACK);
}

/* Check for score updates. */
void PlayingState::CheckScore() {

	if (_displayedScore != GameManager::Instance()->GetScore()) {
		_displayedScore = GameManager::Instance()->GetScore();
		delete _scoreValueText;
		_scoreValueText = new ShadowedText(cScoreValuePos, Text::Align::MIDRIGHT, FNT_M6X11, FNT_SMALL, std::to_string(_displayedScore), WHITE, BLACK);
	}

}


/* Check for level up updates */
void PlayingState::CheckLevel() {

	if (_displayedLevel != GameManager::Instance()->GetLevel()) {

		//Update Level up and next level score texts

		_displayedLevel = GameManager::Instance()->GetLevel();
		delete _levelValueText;
		_levelValueText = new ShadowedText(cLevelValuePos, Text::Align::MIDRIGHT, FNT_M6X11, FNT_SMALL, std::to_string(_displayedLevel), WHITE, BLACK);

		_displayedNextLevelScore = GameManager::Instance()->GetScoreToNextLevel();
		delete _scoreValue2Text;
		_scoreValue2Text = new ShadowedText(cScoreValue2Pos, Text::Align::MIDRIGHT, FNT_M6X11, FNT_SMALL, std::to_string(_displayedNextLevelScore), WHITE, BLACK);

		//LevelUp animation, reset board, and play sound.

		_foregroundStrip1->TransitState(ForegroundStrip::ForegroundStripState::LEVELUP);
		_foregroundStrip2->TransitState(ForegroundStrip::ForegroundStripState::LEVELUP);

		_columnTimer->ResetTimer(GameManager::Instance()->GetTimePerColumn());
		_board->BreakAllGems(true);
		_board->PushColumns(GameManager::Instance()->cStartColumns);

		SoundManager::Instance()->PlaySFX(SoundManager::cLevelUpSound);
	}

}

/* Check for fills updates */
void PlayingState::CheckFills() {
	
	if (_displayedFills != GameManager::Instance()->GetFillsLeft()) {
		_displayedFills = GameManager::Instance()->GetFillsLeft();
		delete _fillsText;
		_fillsText = new ShadowedText(cFillsValuePos, Text::Align::MIDLEFT, FNT_M6X11, FNT_SMALL, std::to_string(_displayedFills), WHITE, BLACK);
	}

}

/* Check for Actions in all buttons (and update click delay in push button) */
void PlayingState::CheckButtons() {

	if (_fillButton->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		if (_board->FillBoard()) {
			SoundManager::Instance()->PlaySFX(SoundManager::cFillSound);
			GameManager::Instance()->UseFill();
		}
	}
	else if (_pauseButton->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->PushState(new PauseScreenState());
		SoundManager::Instance()->PlaySFX(SoundManager::cSelectSound);
	}
	
	else if (_pushButton->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		_board->PushColumns(1);
		_pushButtonTimer->ResetTimer(cPushButtonTimerValue);
		_columnTimer->ResetTimer(GameManager::Instance()->GetTimePerColumn());
	}
	//Check if buttons should be active
	_fillButton->OnlySetActiveIf(GameManager::Instance()->GetFillsLeft() > 0);
	_pushButton->OnlySetActiveIf(_pushButtonTimer->HasEnded());
}

/* Check if game is lost */
void PlayingState::CheckGameOver() {

	if (_board->GetPos().x < _endLine->GetPos().x && !_endGameTimer->IsRunning()) {
		_board->BreakAllGems(false);
		SoundManager::Instance()->StopMusic();
		SoundManager::Instance()->PlaySFX(SoundManager::cLoseSound);
		_endGameTimer->StartTimer();
	}
	else if (_endGameTimer->HasEnded()) {
		Game::Instance()->GetGameStateMachine()->ChangeState(new GameOverScreenState());
	}
}