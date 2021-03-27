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

const int GameOverScreenState::cGameOverTextX    = SCREEN_W / 2;
const int GameOverScreenState::cGameOverTextY    = SCREEN_H / 2 - 50;
const char* GameOverScreenState::cGameOverString = "GAME OVER";

const int GameOverScreenState::cFlavorTextX    = SCREEN_W / 2;
const int GameOverScreenState::cFlavorTextY    = SCREEN_H / 2 - 30;
const char* GameOverScreenState::cFlavorString = "The Gems win this time.";

const int GameOverScreenState::cScoreTextX    = SCREEN_W / 2;
const int GameOverScreenState::cScoreTextY    = 110;

const int GameOverScreenState::cAgainButtonX  = SCREEN_W / 2 - 60 - BigButton::cW / 2;
const int GameOverScreenState::cAgainButtonY  = 140;
const int GameOverScreenState::cAgainContentX = cAgainButtonX + BigButton::cW / 2;
const int GameOverScreenState::cAgainContentY = cAgainButtonY + BigButton::cH / 2;
const char* GameOverScreenState::cAgainString = "PLAY AGAIN";

const int GameOverScreenState::cExitButtonX   = SCREEN_W / 2 + 60 - BigButton::cW / 2;
const int GameOverScreenState::cExitButtonY   = 140;
const int GameOverScreenState::cExitContentX  = cExitButtonX + BigButton::cW / 2;
const int GameOverScreenState::cExitContentY  = cExitButtonY + BigButton::cH / 2;
const char* GameOverScreenState::cExitString  = "EXIT GAME";

//........................................................................

void GameOverScreenState::Init() {

	stateID_ = "GAMEOVERSCREEN";

	//Foreground Strips

	gameObjects_.push_back(new ForegroundStrip(0, 0));
	gameObjects_.push_back(new ForegroundStrip(0, SCREEN_H- ForegroundStrip::cH));

	//Text to be displayed;

	std::string scoreString = "FINAL SCORE: " + std::to_string(GameManager::Instance()->GetScore());

	gameObjects_.push_back(new ShadowedText(cGameOverTextX, cGameOverTextY, Text::Align::MID, FNT_M6X11, 32, cGameOverString, WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(cFlavorTextX, cFlavorTextY, Text::Align::MID, FNT_M3X6, 16, cFlavorString, WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(cScoreTextX, cScoreTextY, Text::Align::MID, FNT_M6X11, 16, scoreString, WHITE, BLACK));

	//Resume and Exit Buttons

	gameObjects_.push_back(againButton_ = new BigButton(cAgainButtonX, cAgainButtonY));
	gameObjects_.push_back(exitButton_ = new BigButton(cExitButtonX, cExitButtonY));

	againButton_->AddContent(new ShadowedText(cAgainContentX, cAgainContentY, Text::Align::MID, FNT_M6X11, 16, cAgainString, WHITE, BLACK));
	exitButton_->AddContent(new ShadowedText(cExitContentX, cExitContentY, Text::Align::MID, FNT_M6X11, 16, cExitString, WHITE, BLACK));
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
