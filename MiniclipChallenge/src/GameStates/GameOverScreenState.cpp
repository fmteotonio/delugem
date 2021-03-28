#include "GameOverScreenState.h"

#include "../Constants.h"
#include "../GameObjects/ForegroundStrip.h"
#include "../GameObjects/Buttons/BigButton.h"
#include "../GameObjects/Texts/ShadowedText.h"
#include "../Game.h"
#include "../SoundManager.h"
#include "../GameManager.h"
#include "../UI.h"
#include "PlayingState.h"
#include "TitleScreenState.h"

//........................GameObject Constants........................

const Position GameOverScreenState::cUpperStripPos = { 0,  0 };
const Position GameOverScreenState::cLowerStripPos = { 0, SCREEN_H - ForegroundStrip::cH };

const Position GameOverScreenState::cGameOverTextPos = { SCREEN_W / 2 , SCREEN_H / 2 - 50 };
const Position GameOverScreenState::cFlavorTextPos =   { SCREEN_W / 2 , SCREEN_H / 2 - 30 };
const Position GameOverScreenState::cScoreTextPos =    { SCREEN_W / 2 , 110 };

const Position GameOverScreenState::cAgainButtonPos = { SCREEN_W / 2 - BigButton::cW / 2 - 60 , 140 };
const Position GameOverScreenState::cExitButtonPos = { SCREEN_W / 2 - BigButton::cW / 2 + 60 , 140 };
const Position GameOverScreenState::cAgainContentPos = { cAgainButtonPos.x + BigButton::cW / 2 , cAgainButtonPos.y + BigButton::cH / 2 };
const Position GameOverScreenState::cExitContentPos = { cExitButtonPos.x + BigButton::cW / 2 , cExitButtonPos.y + BigButton::cH / 2 };

const char* GameOverScreenState::cGameOverString = "GAME OVER";
const char* GameOverScreenState::cFlavorString = "The Gems win this time.";
const char* GameOverScreenState::cAgainString = "PLAY AGAIN";
const char* GameOverScreenState::cExitString  = "EXIT GAME";

//........................................................................

void GameOverScreenState::Init() {

	stateID_ = "GAMEOVERSCREEN";

	//Foreground Strips

	Position p1 = { 0,0 };
	Position p2 = { 0, SCREEN_H - ForegroundStrip::cH };

	gameObjects_.push_back(new ForegroundStrip(p1));
	gameObjects_.push_back(new ForegroundStrip(p2));

	//Text to be displayed;

	std::string scoreString = "FINAL SCORE: " + std::to_string(GameManager::Instance()->GetScore());

	gameObjects_.push_back(new ShadowedText(cGameOverTextPos, Text::Align::MID, FNT_M6X11, 32, cGameOverString, WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(cFlavorTextPos, Text::Align::MID, FNT_M3X6, 16, cFlavorString, WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(cScoreTextPos, Text::Align::MID, FNT_M6X11, 16, scoreString, WHITE, BLACK));

	//Resume and Exit Buttons

	gameObjects_.push_back(againButton_ = new BigButton(cAgainButtonPos));
	gameObjects_.push_back(exitButton_ = new BigButton(cExitButtonPos));

	againButton_->AddContent(new ShadowedText(cAgainContentPos, Text::Align::MID, FNT_M6X11, 16, cAgainString, WHITE, BLACK));
	exitButton_->AddContent(new ShadowedText(cExitContentPos, Text::Align::MID, FNT_M6X11, 16, cExitString, WHITE, BLACK));
}

void GameOverScreenState::Update(int deltaTime) {
	GameState::Update(deltaTime);

	if (againButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->ChangeState(new PlayingState());
		SoundManager::Instance()->PlaySFX("GameStart",false);
	}
	else if (exitButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->ChangeState(new TitleScreenState());
		SoundManager::Instance()->PlaySFX("ButtonSelect", false);
	}
		
}
