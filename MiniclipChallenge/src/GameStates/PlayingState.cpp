#include "PlayingState.h"

#include "../GameObjects/EndLine.h"
#include "../GameObjects/ForegroundStrip.h"
#include "../GameObjects/Board.h"
#include "../GameObjects/Clock.h"
#include "../GameObjects/Buttons/SmallButton.h"
#include "../GameObjects/Texts/ShadowedText.h"
#include "../GameObjects/Texts/VerticalShadowedText.h"
#include "../GameObjects/StaticImages/SmallIcon.h"
#include "../GameStates/PauseScreenState.h"
#include "../GameStates/GameOverScreenState.h"
#include "../Constants.h"
#include "../GameManager.h"
#include "../SoundManager.h"
#include "../Game.h"

//..........................GameObject Constants........................

const Position PlayingState::cUpperStripPos = { 0,  0 };
const Position PlayingState::cLowerStripPos = { 0, SCREEN_H - ForegroundStrip::cDim.h };

const Position PlayingState::cBoardPos   = { SCREEN_W , 28 + Gem::cDim.h * (10 - Board::cColumnSize) };
const Position PlayingState::cEndLinePos = { GameManager::cEndGemsMargin * Gem::cDim.w , 28 };
const Position PlayingState::cEndTextPos = { std::round(PlayingState::cEndLinePos.x / 1.1) , 67 };
const Position PlayingState::cClockPos   = { 290, 193 };

const int PlayingState::cEndTextSpacing = -4;

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

//........................................................................

void PlayingState::Init() {

	stateID_ = "PLAYING";

	// Timers
	// columnTimer:		Time until a new column is pushed into the board;
	// pushButtonTimer: Small delay to consecutive column pushes;
	// endGameTimer:	Small delay when game is lost;

	_columnTimer = new Timer(GameManager::Instance()->TimePerColumn(), true);
	_pushButtonTimer = new Timer(-1, true);
	_endGameTimer = new Timer(500, false);

	//Reset game and init Board

	GameManager::Instance()->Reset();

	_gameObjects.push_back(_board = new Board(cBoardPos, true));
	_board->PushColumn(GameManager::Instance()->cStartColumns);

	//End Line and Text

	_gameObjects.push_back(_endLine = new EndLine(cEndLinePos));
	_gameObjects.push_back(new VerticalShadowedText(cEndTextPos, Text::Align::MID, FNT_M3X6, 16, cEndTextSpacing, "END ZONE", WHITE, BLACK));

	//Foreground Strips

	_gameObjects.push_back(_foregroundStrip1 = new ForegroundStrip(cUpperStripPos));
	_gameObjects.push_back(_foregroundStrip2 = new ForegroundStrip(cLowerStripPos));

	//Clock displaying ColumnTimer progress

	_gameObjects.push_back(_pushClock = new Clock(cClockPos, _columnTimer));
	
	//Init all text and button objects

	InitUI();
}

void PlayingState::InitUI() {

	//Static text elements

	_gameObjects.push_back(new ShadowedText(cScoreTextPos, Text::Align::MIDLEFT, FNT_M6X11, 16, "SCORE:", WHITE, BLACK));
	_gameObjects.push_back(new ShadowedText(cLevelTextPos, Text::Align::MIDLEFT, FNT_M6X11, 16, "LEVEL:", WHITE, BLACK));
	_gameObjects.push_back(new ShadowedText(cPushTextPos, Text::Align::MIDLEFT, FNT_M6X11, 16, "PUSH", WHITE, BLACK));
	_gameObjects.push_back(new ShadowedText(cFillsTextPos, Text::Align::MIDLEFT, FNT_M6X11, 16, "FILL (", WHITE, BLACK));
	_gameObjects.push_back(new ShadowedText(cFillsText2Pos, Text::Align::MIDLEFT, FNT_M6X11, 16, "left)", WHITE, BLACK));
	_gameObjects.push_back(new ShadowedText(cScoreText2Pos, Text::Align::MIDRIGHT, FNT_M6X11, 16, " / ", WHITE, BLACK));

	//Buttons
	_gameObjects.push_back(_fillButton = new SmallButton(cFillsButtonPos));
	_gameObjects.push_back(_pauseButton = new SmallButton(cPauseButtonPos));
	_gameObjects.push_back(_pushButton = new SmallButton(cPushButtonPos));

	//Button Icons
	_pauseButton->AddContent(new SmallIcon(cPauseContentPos, cPauseIconPath));
	_pushButton->AddContent(new SmallIcon(cPushContentPos,   cPushIconPath));
	_fillButton->AddContent(new SmallIcon(cFillsContentPos,  cFillIconPath));

	//Dynamic text elements
	_displayedScore = GameManager::Instance()->GetScore();
	_displayedLevel = GameManager::Instance()->GetLevel();
	_displayedFills = GameManager::Instance()->GetFillsLeft();
	_displayedNextLevelScore = GameManager::Instance()->GetScoreToNextLevel();

	_scoreValueText = new ShadowedText(cScoreValuePos, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(_displayedScore), WHITE, BLACK);
	_levelValueText = new ShadowedText(cLevelValuePos, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(_displayedLevel), WHITE, BLACK);
	_fillsText = new ShadowedText(cFillsValuePos, Text::Align::MIDLEFT, FNT_M6X11, 16, std::to_string(_displayedFills), WHITE, BLACK);
	_nextLevelScoreValueText = new ShadowedText(cScoreValue2Pos, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(_displayedNextLevelScore), WHITE, BLACK);

}

void PlayingState::Update(int deltaTime) {
	GameState::Update(deltaTime);

	_columnTimer->Update(deltaTime);
	_pushButtonTimer->Update(deltaTime);
	_endGameTimer->Update(deltaTime);

	_pushClock->UpdateFrame();

	if (_columnTimer->HasRung()) {
		_board->PushColumn(1);
		_pushButtonTimer->ResetTimer(100);
		_columnTimer->ResetTimer(GameManager::Instance()->TimePerColumn());
	}

	//Check if score text needs update
	if (_displayedScore != GameManager::Instance()->GetScore()) {
		_displayedScore = GameManager::Instance()->GetScore();
		delete _scoreValueText;
		_scoreValueText = new ShadowedText(cScoreValuePos, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(_displayedScore), WHITE, BLACK);
	}
	//Check if level text needs update
	if (_displayedLevel != GameManager::Instance()->GetLevel()) {
		_displayedLevel = GameManager::Instance()->GetLevel();
		delete _levelValueText;
		_levelValueText = new ShadowedText(cLevelValuePos, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(_displayedLevel), WHITE, BLACK);


		_displayedNextLevelScore = GameManager::Instance()->GetScoreToNextLevel();
		delete _nextLevelScoreValueText;
		_nextLevelScoreValueText = new ShadowedText(cScoreValue2Pos, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(_displayedNextLevelScore), WHITE, BLACK);
		


		//LevelUp animation in foregroundStrips
		_foregroundStrip1->TransitState(ForegroundStrip::ForegroundStripState::LEVELUP);
		_foregroundStrip2->TransitState(ForegroundStrip::ForegroundStripState::LEVELUP);

		_board->DestroyAllGems(true);
		_board->PushColumn(13);
	}
	//Check if fills text needs update
	if (_displayedFills != GameManager::Instance()->GetFillsLeft()) {
		_displayedFills = GameManager::Instance()->GetFillsLeft();
		delete _fillsText;
		_fillsText = new ShadowedText(cFillsValuePos, Text::Align::MIDLEFT, FNT_M6X11, 16, std::to_string(_displayedFills), WHITE, BLACK);
	}

	//Check for actions in all buttons (and update click delay in push button)
	if (_fillButton->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		if (_board->FillBoard()) {
			SoundManager::Instance()->PlaySFX("Fill", false);
			GameManager::Instance()->UseFill();
		}
	}
	else if (_pauseButton->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->PushState(new PauseScreenState());
		SoundManager::Instance()->PlaySFX("ButtonSelect", false);
	}
	else if (_pushButton->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		_board->PushColumn(1);
		_pushButtonTimer->ResetTimer(100);
		_columnTimer->ResetTimer(GameManager::Instance()->TimePerColumn());
	}
	

	//Check if buttons should be active
	_fillButton->OnlySetActiveIf(GameManager::Instance()->GetFillsLeft() > 0);
	_pushButton->OnlySetActiveIf(_pushButtonTimer->HasRung());

	//Check if game is lost
	if (_board->GetPos().x < _endLine->GetPos().x && !_endGameTimer->IsRunning()) {
		_board->DestroyAllGems(false);
		SoundManager::Instance()->PlaySFX("GameOver", false);
		_endGameTimer->StartTimer();
	}
	else if (_endGameTimer->HasRung()) {
		Game::Instance()->GetGameStateMachine()->ChangeState(new GameOverScreenState());
	}
}

void PlayingState::Render() {
	GameState::Render();

	_scoreValueText->Render();
	_levelValueText->Render();
	_fillsText->Render();
	_nextLevelScoreValueText->Render();
}

void PlayingState::Clean() {
	GameState::Clean();

	_scoreValueText->Clean();
	_levelValueText->Clean();
	_fillsText->Clean();
	_nextLevelScoreValueText->Clean();
	delete _scoreValueText;
	delete _levelValueText;
	delete _fillsText;
	delete _nextLevelScoreValueText;

	delete _pushButtonTimer;
	delete _columnTimer;
	delete _endGameTimer;
}