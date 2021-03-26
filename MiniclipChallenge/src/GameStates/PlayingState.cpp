#include "PlayingState.h"

#include "../GameObjects/EndLine.h"
#include "../GameObjects/ForegroundStrip.h"
#include "../GameObjects/Board.h"
#include "../GameObjects/Button.h"
#include "../GameObjects/ShadowedText.h"
#include "../GameObjects/StaticImage.h"
#include "../GameStates/PauseScreenState.h"
#include "../GameStates/GameOverScreenState.h"
#include "../Constants.h"
#include "../GameManager.h"
#include "../SoundManager.h"
#include "../Game.h"


void PlayingState::Init() {

	stateID_ = "PLAYING";

	gameObjects_.push_back(board_ = new Board(BOARD_START_X, BOARD_START_Y));
	gameObjects_.push_back(new EndLine(ENDLINE_X, ENDLINE_Y));

	gameObjects_.push_back(foregroundStrip1_ = new ForegroundStrip(0, 0));
	gameObjects_.push_back(foregroundStrip2_ = new ForegroundStrip(0, SCREEN_HEIGHT - FOREGROUNDSTRIP_H));
	
	//Static text elements
	gameObjects_.push_back(new ShadowedText(SCORETEXT_X, SCORETEXT_Y,   Text::Align::MIDLEFT, FNT_M6X11, 16, "SCORE:", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(LEVELTEXT_X, LEVELTEXT_Y,   Text::Align::MIDLEFT, FNT_M6X11, 16, "LEVEL:", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(PUSHTEXT_X,  PUSHTEXT_Y,    Text::Align::MIDLEFT, FNT_M6X11, 16, "PUSH",   WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(FILLTEXT1_X, FILLTEXT1_Y,   Text::Align::MIDLEFT, FNT_M6X11, 16, "FILL (", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(FILLTEXT2_X, FILLTEXT2_Y,   Text::Align::MIDLEFT, FNT_M6X11, 16, "left)",  WHITE, BLACK));

	//Buttons
	gameObjects_.push_back(pauseButton_ = new Button(PAUSEBUTTON_X, PAUSEBUTTON_Y, SMALLBUTTON_W, SMALLBUTTON_H, SPR_SMALLBUTTON));
	gameObjects_.push_back(pushButton_  = new Button(PUSHBUTTON_X,  PUSHBUTTON_Y,  SMALLBUTTON_W, SMALLBUTTON_H, SPR_SMALLBUTTON));
	gameObjects_.push_back(fillButton_  = new Button(FILLBUTTON_X,  FILLBUTTON_Y,  SMALLBUTTON_W, SMALLBUTTON_H, SPR_SMALLBUTTON));

	//Button Icons
	pauseButton_->AddContent(new StaticImage(PAUSEICON_X, PAUSEICON_Y, ICON_W, ICON_H, SPR_ICONPAUSE));
	pushButton_ ->AddContent(new StaticImage(PUSHICON_X,  PUSHICON_Y,  ICON_W, ICON_H, SPR_ICONPUSH));
	fillButton_ ->AddContent(new StaticImage(FILLICON_X,  FILLICON_Y,  ICON_W, ICON_H, SPR_ICONFILL));
	
	//Dynamic text elements
	displayedScore_ = GameManager::Instance()->score();
	displayedLevel_ = GameManager::Instance()->level();
	displayedFills_ = GameManager::Instance()->fillsLeft();
	scoreValueText_ = new ShadowedText(SCOREVALUE_X, SCOREVALUE_Y, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedScore_), WHITE, BLACK);
	levelValueText_ = new ShadowedText(LEVELVALUE_X, LEVELVALUE_Y, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedLevel_), WHITE, BLACK);
	fillsText_      = new ShadowedText(FILLVALUE_X, FILLVALUE_Y,   Text::Align::MIDLEFT,  FNT_M6X11, 16, std::to_string(displayedFills_), WHITE, BLACK);

}

void PlayingState::Update(int deltaTime) {
	GameState::Update(deltaTime);

	//Check if score text needs update
	if (displayedScore_ != GameManager::Instance()->score()) {
		displayedScore_ = GameManager::Instance()->score();
		delete scoreValueText_;
		scoreValueText_ = new ShadowedText(SCOREVALUE_X, SCOREVALUE_Y, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedScore_), WHITE, BLACK);
	}
	//Check if level text needs update
	if (displayedLevel_ != GameManager::Instance()->level()) {
		displayedLevel_ = GameManager::Instance()->level();
		delete levelValueText_;
		levelValueText_ = new ShadowedText(LEVELVALUE_X, LEVELVALUE_Y, Text::Align::MIDRIGHT, FNT_M6X11, 16, std::to_string(displayedLevel_), WHITE, BLACK);

		foregroundStrip1_->TransitState(ForegroundStrip::ForegroundStripState::LEVELUP);
		foregroundStrip2_->TransitState(ForegroundStrip::ForegroundStripState::LEVELUP);
	}
	//Check if fills text needs update
	if (displayedFills_ != GameManager::Instance()->fillsLeft()) {
		displayedFills_ = GameManager::Instance()->fillsLeft();
		delete fillsText_;
		fillsText_ = new ShadowedText(FILLVALUE_X, FILLVALUE_Y, Text::Align::MIDLEFT, FNT_M6X11, 16, std::to_string(displayedFills_), WHITE, BLACK);
	}
	//Check for actions in push and fill buttons
	if (pushButton_->buttonState() == Button::ButtonState::PRESS_ACTION)
		board_->pushColumn(1);
	if (fillButton_->buttonState() == Button::ButtonState::PRESS_ACTION)
		board_->fillBoard();
	if (pauseButton_->buttonState() == Button::ButtonState::PRESS_ACTION)
		Game::Instance()->gameStateMachine()->pushState(new PauseScreenState());

	if (GameManager::Instance()->fillsLeft() == 0 && fillButton_->buttonState() != Button::ButtonState::INACTIVE)
		fillButton_->TransitState(Button::ButtonState::INACTIVE);
	if (GameManager::Instance()->fillsLeft() >  0 && fillButton_->buttonState() == Button::ButtonState::INACTIVE)
		fillButton_->TransitState(Button::ButtonState::DEFAULT);
	if (board_->gameLost()) {
		Game::Instance()->gameStateMachine()->changeState(new GameOverScreenState());
		SoundManager::Instance()->playSFX("GameOver", false);
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
}