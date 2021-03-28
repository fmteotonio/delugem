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
#include "../UI.h"

#include <algorithm>

//........................GameObject Constants........................

const Position PlayingState::cBoardPos   = { SCREEN_W , 28 + Gem::cH * (10 - Board::cColumnSize) };
const Position PlayingState::cEndLinePos = { GameManager::cEndGemsMargin * Gem::cW , 28 };
const Position PlayingState::cEndTextPos = { std::round(PlayingState::cEndLinePos.x / 1.1) , 67 };
const Position PlayingState::cClockPos = { 290, 193 };

const int PlayingState::cEndTextSpacing = -4;

//........................................................................

void PlayingState::Init() {

	stateID_ = "PLAYING";

	GameManager::Instance()->Reset();

	gameObjects_.push_back(board_ = new Board(cBoardPos, true));
	board_->PushColumn(GameManager::Instance()->cStartColumns);

	columnTimer_ = new Timer(GameManager::Instance()->TimePerColumn(), true);
	pushButtonTimer_ = new Timer(-1, true);
	endGameTimer_ = new Timer(500, false);

	gameObjects_.push_back(endLine_ = new EndLine(cEndLinePos));
	gameObjects_.push_back(new VerticalShadowedText(cEndTextPos, Text::Align::MID, FNT_M3X6, 16, cEndTextSpacing, "END ZONE", WHITE, BLACK));

	Position p1 = { 0,0 };
	Position p2 = { 0, SCREEN_H - ForegroundStrip::cH };

	gameObjects_.push_back(foregroundStrip1_ = new ForegroundStrip(p1));
	gameObjects_.push_back(foregroundStrip2_ = new ForegroundStrip(p2));

	gameObjects_.push_back(pushClock_ = new Clock(cClockPos, columnTimer_));
	
	//Static text elements

	gameObjects_.push_back(new ShadowedText(UI::cScoreTextPos, Text::Align::MIDLEFT, FNT_M6X11, 16, "SCORE:", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(UI::cLevelTextPos, Text::Align::MIDLEFT, FNT_M6X11, 16, "LEVEL:", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(UI::cPushTextPos, Text::Align::MIDLEFT, FNT_M6X11, 16, "PUSH", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(UI::cFillsTextPos, Text::Align::MIDLEFT, FNT_M6X11, 16, "FILL (", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(UI::cFillsText2Pos, Text::Align::MIDLEFT, FNT_M6X11, 16, "left)", WHITE, BLACK));

	//Buttons
	gameObjects_.push_back(fillButton_ = new SmallButton(UI::cFillsButtonPos));
	gameObjects_.push_back(pauseButton_ = new SmallButton(UI::cPauseButtonPos));
	gameObjects_.push_back(pushButton_ = new SmallButton(UI::cPushButtonPos));

	//Button Icons
	pauseButton_->AddContent(new SmallIcon(UI::cPauseContentPos, UI::cPauseIconPath));
	pushButton_->AddContent(new SmallIcon(UI::cPushContentPos, UI::cPushIconPath));
	fillButton_->AddContent(new SmallIcon(UI::cFillsContentPos, UI::cFillIconPath));
	
	//Dynamic text elements
	displayedScore_ = GameManager::Instance()->GetScore();
	displayedLevel_ = GameManager::Instance()->GetLevel();
	displayedFills_ = GameManager::Instance()->GetFillsLeft();

	scoreValueText_ = new ShadowedText(UI::cScoreValuePos, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedScore_), WHITE, BLACK);
	levelValueText_ = new ShadowedText(UI::cLevelValuePos, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedLevel_), WHITE, BLACK);
	fillsText_ = new ShadowedText(UI::cFillsValuePos, Text::Align::MIDLEFT, FNT_M6X11, 16, std::to_string(displayedFills_), WHITE, BLACK);
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
		scoreValueText_ = new ShadowedText(UI::cScoreValuePos, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedScore_), WHITE, BLACK);
	}
	//Check if level text needs update
	if (displayedLevel_ != GameManager::Instance()->GetLevel()) {
		displayedLevel_ = GameManager::Instance()->GetLevel();
		delete levelValueText_;
		levelValueText_ = new ShadowedText(UI::cLevelValuePos, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedLevel_), WHITE, BLACK);

		//LevelUp animation in foregroundStrips
		foregroundStrip1_->TransitState(ForegroundStrip::ForegroundStripState::LEVELUP);
		foregroundStrip2_->TransitState(ForegroundStrip::ForegroundStripState::LEVELUP);
	}
	//Check if fills text needs update
	if (displayedFills_ != GameManager::Instance()->GetFillsLeft()) {
		displayedFills_ = GameManager::Instance()->GetFillsLeft();
		delete fillsText_;
		fillsText_ = new ShadowedText(UI::cFillsValuePos, Text::Align::MIDLEFT, FNT_M6X11, 16, std::to_string(displayedFills_), WHITE, BLACK);
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