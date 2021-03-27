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

const int PlayingState::cBoardX = SCREEN_W;
const int PlayingState::cBoardY = 28 + Gem::cH * (10 - Board::cColumnSize);

const int PlayingState::cEndLineX = GameManager::cEndGemsMargin * Gem::cW;
const int PlayingState::cEndLineY = 28;

const int PlayingState::cEndTextX = std::round(PlayingState::cEndLineX / 1.1);
const int PlayingState::cEndTextY = 67;
const int PlayingState::cEndTextSpacing = -4;

void PlayingState::Init() {

	stateID_ = "PLAYING";

	gameObjects_.push_back(board_ = new Board(cBoardX, cBoardY));
	columnTimer_ = new Timer(GameManager::Instance()->TimePerColumn(), true);
	

	
	gameObjects_.push_back(endLine_ = new EndLine(cEndLineX, cEndLineY));
	gameObjects_.push_back(new VerticalShadowedText(cEndTextX, cEndTextY, Text::Align::MID, FNT_M3X6, 16, cEndTextSpacing, "END ZONE", WHITE, BLACK));

	gameObjects_.push_back(foregroundStrip1_ = new ForegroundStrip(0, 0));
	gameObjects_.push_back(foregroundStrip2_ = new ForegroundStrip(0, SCREEN_H - ForegroundStrip::cH));

	gameObjects_.push_back(pushClock_ = new Clock(UI::cPushTextX - 23, UI::cBotTextY-9, columnTimer_));
	
	//Static text elements

	gameObjects_.push_back(new ShadowedText(UI::cScoreTextX, UI::cTopTextY, Text::Align::MIDLEFT, FNT_M6X11, 16, "SCORE:", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(UI::cLevelTextX, UI::cTopTextY, Text::Align::MIDLEFT, FNT_M6X11, 16, "LEVEL:", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(UI::cPushTextX,  UI::cBotTextY, Text::Align::MIDLEFT, FNT_M6X11, 16, "PUSH",   WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(UI::cFillsTextX, UI::cBotTextY, Text::Align::MIDLEFT, FNT_M6X11, 16, "FILL (", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(UI::cFillsText2X,UI::cBotTextY, Text::Align::MIDLEFT, FNT_M6X11, 16, "left)",  WHITE, BLACK));

	//Buttons
	gameObjects_.push_back(fillButton_ = new SmallButton(UI::cFillsButtonX, UI::cBotButtonY));
	gameObjects_.push_back(pauseButton_ = new SmallButton(UI::cPauseButtonX, UI::cTopButtonY));
	gameObjects_.push_back(pushButton_  = new SmallButton(UI::cPushButtonX,  UI::cBotButtonY));

	pushButtonTimer_ = new Timer(-1, true);

	//Button Icons
	pauseButton_->AddContent(new SmallIcon(UI::cPauseButtonX + UI::cIconPadding, UI::cTopButtonY + UI::cIconPadding, UI::cPauseIconPath));
	pushButton_ ->AddContent(new SmallIcon(UI::cPushButtonX  + UI::cIconPadding, UI::cBotButtonY + UI::cIconPadding, UI::cPushIconPath));
	fillButton_ ->AddContent(new SmallIcon(UI::cFillsButtonX + UI::cIconPadding, UI::cBotButtonY + UI::cIconPadding, UI::cFillIconPath));
	
	//Dynamic text elements
	displayedScore_ = GameManager::Instance()->GetScore();
	displayedLevel_ = GameManager::Instance()->GetLevel();
	displayedFills_ = GameManager::Instance()->GetFillsLeft();
	scoreValueText_ = new ShadowedText(UI::cScoreValueX, UI::cTopTextY, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedScore_), WHITE, BLACK);
	levelValueText_ = new ShadowedText(UI::cLevelValueX, UI::cTopTextY, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedLevel_), WHITE, BLACK);
	fillsText_      = new ShadowedText(UI::cFillsValueX, UI::cBotTextY, Text::Align::MIDLEFT,  FNT_M6X11, 16, std::to_string(displayedFills_), WHITE, BLACK);

}

void PlayingState::Update(int deltaTime) {
	GameState::Update(deltaTime);

	columnTimer_->Update(deltaTime);
	pushClock_->Update();
	if (columnTimer_->HasRung()) {
		board_->PushColumn(1);
		pushButtonTimer_->ResetTimer(100);
		columnTimer_->ResetTimer(GameManager::Instance()->TimePerColumn());
	}

	//Check if score text needs update
	if (displayedScore_ != GameManager::Instance()->GetScore()) {
		displayedScore_ = GameManager::Instance()->GetScore();
		delete scoreValueText_;
		scoreValueText_ = new ShadowedText(UI::cScoreValueX, UI::cTopTextY, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedScore_), WHITE, BLACK);
	}
	//Check if level text needs update
	if (displayedLevel_ != GameManager::Instance()->GetLevel()) {
		displayedLevel_ = GameManager::Instance()->GetLevel();
		delete levelValueText_;
		levelValueText_ = new ShadowedText(UI::cLevelValueX, UI::cTopTextY, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedLevel_), WHITE, BLACK);

		//LevelUp animation in foregroundStrips
		foregroundStrip1_->TransitState(ForegroundStrip::ForegroundStripState::LEVELUP);
		foregroundStrip2_->TransitState(ForegroundStrip::ForegroundStripState::LEVELUP);
	}
	//Check if fills text needs update
	if (displayedFills_ != GameManager::Instance()->GetFillsLeft()) {
		displayedFills_ = GameManager::Instance()->GetFillsLeft();
		delete fillsText_;
		fillsText_ = new ShadowedText(UI::cFillsValueX, UI::cBotTextY, Text::Align::MIDLEFT, FNT_M6X11, 16, std::to_string(displayedFills_), WHITE, BLACK);
	}

	//Check for actions in all buttons (and update click delay in push button)
	if (fillButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION)
		board_->FillBoard();
	else if (pauseButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION)
		Game::Instance()->GetGameStateMachine()->PushState(new PauseScreenState());
	else if (pushButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		board_->PushColumn(1);
		pushButtonTimer_->ResetTimer(100);
		columnTimer_->ResetTimer(GameManager::Instance()->TimePerColumn());
	}
	pushButtonTimer_->Update(deltaTime);

	//Check if buttons should be active
	fillButton_->OnlySetActiveIf(GameManager::Instance()->GetFillsLeft() > 0);
	pushButton_->OnlySetActiveIf(pushButtonTimer_->HasRung());

	//Check if game is lost
	if (board_->GetX() < endLine_->GetX()) {
		Game::Instance()->GetGameStateMachine()->ChangeState(new GameOverScreenState());
		SoundManager::Instance()->PlaySFX("GameOver", false);
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
}