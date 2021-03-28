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
const Position PlayingState::cLowerStripPos = { 0, SCREEN_H - ForegroundStrip::cH };

const Position PlayingState::cBoardPos   = { SCREEN_W , 28 + Gem::cH * (10 - Board::cColumnSize) };
const Position PlayingState::cEndLinePos = { GameManager::cEndGemsMargin * Gem::cW , 28 };
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
const Position PlayingState::cPushTextPos   = { 313,  cBotTextY };
const Position PlayingState::cFillsTextPos  = { 7,  cBotTextY };
const Position PlayingState::cFillsText2Pos = { cFillsTextPos.x + 50, cBotTextY };

const Position PlayingState::cLevelValuePos = { cLevelTextPos.x + 71 , cTopTextY };
const Position PlayingState::cScoreValuePos = { cScoreTextPos.x + 99 , cTopTextY };
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

	columnTimer_ = new Timer(GameManager::Instance()->TimePerColumn(), true);
	pushButtonTimer_ = new Timer(-1, true);
	endGameTimer_ = new Timer(500, false);

	//Reset game and init Board

	GameManager::Instance()->Reset();

	gameObjects_.push_back(board_ = new Board(cBoardPos, true));
	board_->PushColumn(GameManager::Instance()->cStartColumns);

	//End Line and Text

	gameObjects_.push_back(endLine_ = new EndLine(cEndLinePos));
	gameObjects_.push_back(new VerticalShadowedText(cEndTextPos, Text::Align::MID, FNT_M3X6, 16, cEndTextSpacing, "END ZONE", WHITE, BLACK));

	//Foreground Strips

	gameObjects_.push_back(foregroundStrip1_ = new ForegroundStrip(cUpperStripPos));
	gameObjects_.push_back(foregroundStrip2_ = new ForegroundStrip(cLowerStripPos));

	//Clock displaying ColumnTimer progress

	gameObjects_.push_back(pushClock_ = new Clock(cClockPos, columnTimer_));
	
	//Init all text and button objects

	InitUI();
}

void PlayingState::InitUI() {

	//Static text elements

	gameObjects_.push_back(new ShadowedText(cScoreTextPos, Text::Align::MIDLEFT, FNT_M6X11, 16, "SCORE:", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(cLevelTextPos, Text::Align::MIDLEFT, FNT_M6X11, 16, "LEVEL:", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(cPushTextPos, Text::Align::MIDLEFT, FNT_M6X11, 16, "PUSH", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(cFillsTextPos, Text::Align::MIDLEFT, FNT_M6X11, 16, "FILL (", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(cFillsText2Pos, Text::Align::MIDLEFT, FNT_M6X11, 16, "left)", WHITE, BLACK));

	//Buttons
	gameObjects_.push_back(fillButton_ = new SmallButton(cFillsButtonPos));
	gameObjects_.push_back(pauseButton_ = new SmallButton(cPauseButtonPos));
	gameObjects_.push_back(pushButton_ = new SmallButton(cPushButtonPos));

	//Button Icons
	pauseButton_->AddContent(new SmallIcon(cPauseContentPos, cPauseIconPath));
	pushButton_->AddContent(new SmallIcon(cPushContentPos,   cPushIconPath));
	fillButton_->AddContent(new SmallIcon(cFillsContentPos,  cFillIconPath));

	//Dynamic text elements
	displayedScore_ = GameManager::Instance()->GetScore();
	displayedLevel_ = GameManager::Instance()->GetLevel();
	displayedFills_ = GameManager::Instance()->GetFillsLeft();

	scoreValueText_ = new ShadowedText(cScoreValuePos, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedScore_), WHITE, BLACK);
	levelValueText_ = new ShadowedText(cLevelValuePos, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedLevel_), WHITE, BLACK);
	fillsText_ = new ShadowedText(cFillsValuePos, Text::Align::MIDLEFT, FNT_M6X11, 16, std::to_string(displayedFills_), WHITE, BLACK);

}

void PlayingState::Update(int deltaTime) {
	GameState::Update(deltaTime);

	columnTimer_->Update(deltaTime);
	pushButtonTimer_->Update(deltaTime);
	endGameTimer_->Update(deltaTime);

	pushClock_->UpdateFrame();

	if (columnTimer_->HasRung()) {
		board_->PushColumn(1);
		pushButtonTimer_->ResetTimer(100);
		columnTimer_->ResetTimer(GameManager::Instance()->TimePerColumn());
	}

	//Check if score text needs update
	if (displayedScore_ != GameManager::Instance()->GetScore()) {
		displayedScore_ = GameManager::Instance()->GetScore();
		delete scoreValueText_;
		scoreValueText_ = new ShadowedText(cScoreValuePos, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedScore_), WHITE, BLACK);
	}
	//Check if level text needs update
	if (displayedLevel_ != GameManager::Instance()->GetLevel()) {
		displayedLevel_ = GameManager::Instance()->GetLevel();
		delete levelValueText_;
		levelValueText_ = new ShadowedText(cLevelValuePos, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedLevel_), WHITE, BLACK);

		//LevelUp animation in foregroundStrips
		foregroundStrip1_->TransitState(ForegroundStrip::ForegroundStripState::LEVELUP);
		foregroundStrip2_->TransitState(ForegroundStrip::ForegroundStripState::LEVELUP);
	}
	//Check if fills text needs update
	if (displayedFills_ != GameManager::Instance()->GetFillsLeft()) {
		displayedFills_ = GameManager::Instance()->GetFillsLeft();
		delete fillsText_;
		fillsText_ = new ShadowedText(cFillsValuePos, Text::Align::MIDLEFT, FNT_M6X11, 16, std::to_string(displayedFills_), WHITE, BLACK);
	}

	//Check for actions in all buttons (and update click delay in push button)
	if (fillButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		if (board_->FillBoard()) {
			SoundManager::Instance()->PlaySFX("Fill", false);
			GameManager::Instance()->UseFill();
		}
	}
	else if (pauseButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->PushState(new PauseScreenState());
		SoundManager::Instance()->PlaySFX("ButtonSelect", false);
	}
	else if (pushButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		board_->PushColumn(1);
		pushButtonTimer_->ResetTimer(100);
		columnTimer_->ResetTimer(GameManager::Instance()->TimePerColumn());
	}
	

	//Check if buttons should be active
	fillButton_->OnlySetActiveIf(GameManager::Instance()->GetFillsLeft() > 0);
	pushButton_->OnlySetActiveIf(pushButtonTimer_->HasRung());

	//Check if game is lost
	if (board_->GetPos().x < endLine_->GetPos().x && !endGameTimer_->IsRunning()) {
		board_->DestroyAllGems();
		SoundManager::Instance()->PlaySFX("GameOver", false);
		endGameTimer_->StartTimer();
	}
	else if (board_->beingDestroyedGems_.empty() && endGameTimer_->HasRung()) {
		Game::Instance()->GetGameStateMachine()->ChangeState(new GameOverScreenState());
	}
}

void PlayingState::Render() {
	GameState::Render();

	scoreValueText_->Render();
	levelValueText_->Render();
	fillsText_->Render();
}

void PlayingState::Clean() {
	GameState::Clean();

	scoreValueText_->Clean();
	levelValueText_->Clean();
	fillsText_->Clean();
	delete scoreValueText_;
	delete levelValueText_;
	delete fillsText_;

	delete pushButtonTimer_;
	delete columnTimer_;
	delete endGameTimer_;
}