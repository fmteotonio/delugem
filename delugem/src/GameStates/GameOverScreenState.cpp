#include "GameOverScreenState.h"

#include "PlayingState.h"
#include "TitleScreenState.h"
#include "../gameObjects/buttons/BigButton.h"
#include "../gameObjects/texts/ShadowedText.h"
#include "../gameObjects/ForegroundStrip.h"
#include "../Constants.h"
#include "../Game.h"
#include "../GameManager.h"
#include "../SoundManager.h"

//........................GameObject Constants........................

const Position GameOverScreenState::cUpperStripPos = { 0,  0 };
const Position GameOverScreenState::cLowerStripPos = { 0, SCREEN_H - ForegroundStrip::cDestDim.h };

const Position GameOverScreenState::cGameOverTextPos = { SCREEN_W / 2 , SCREEN_H / 2 - 50 };
const Position GameOverScreenState::cFlavorTextPos =   { SCREEN_W / 2 , SCREEN_H / 2 - 30 };
const Position GameOverScreenState::cScoreTextPos =    { SCREEN_W / 2 , 110 };

const Position GameOverScreenState::cAgainButtonPos =  { SCREEN_W / 2 - BigButton::cDim.w / 2 - 60 , 140 };
const Position GameOverScreenState::cExitButtonPos =   { SCREEN_W / 2 - BigButton::cDim.w / 2 + 60 , 140 };
const Position GameOverScreenState::cAgainContentPos = { cAgainButtonPos.x + BigButton::cDim.w / 2 , cAgainButtonPos.y + BigButton::cDim.h / 2 };
const Position GameOverScreenState::cExitContentPos =  { cExitButtonPos.x + BigButton::cDim.w / 2 , cExitButtonPos.y + BigButton::cDim.h / 2 };

const char* GameOverScreenState::cGameOverString =     "GAME OVER";
const char* GameOverScreenState::cFlavorString =       "The Gems win this time.";
const char* GameOverScreenState::cScorePartialString = "FINAL SCORE: ";
const char* GameOverScreenState::cAgainString =	       "PLAY AGAIN";
const char* GameOverScreenState::cExitString  =        "EXIT GAME";

//........................................................................

void GameOverScreenState::Init() {

	stateID_ = "GAMEOVERSCREEN";

	//Foreground Strips

	_gameObjects.push_back(new ForegroundStrip(cUpperStripPos));
	_gameObjects.push_back(new ForegroundStrip(cLowerStripPos));

	//Text to be displayed;

	std::string scoreString = cScorePartialString + std::to_string(GameManager::Instance()->GetScore());

	_gameObjects.push_back(new ShadowedText(cGameOverTextPos, Text::Align::MID, FNT_M6X11, FNT_LARGE, cGameOverString, WHITE, BLACK));
	_gameObjects.push_back(new ShadowedText(cFlavorTextPos, Text::Align::MID, FNT_M3X6, FNT_SMALL, cFlavorString, WHITE, BLACK));
	_gameObjects.push_back(new ShadowedText(cScoreTextPos, Text::Align::MID, FNT_M6X11, FNT_SMALL, scoreString, WHITE, BLACK));

	//Resume and Exit Buttons

	_gameObjects.push_back(_againButton = new BigButton(cAgainButtonPos));
	_gameObjects.push_back(_exitButton = new BigButton(cExitButtonPos));

	_againButton->AddContent(new ShadowedText(cAgainContentPos, Text::Align::MID, FNT_M6X11, FNT_SMALL, cAgainString, WHITE, BLACK));
	_exitButton->AddContent(new ShadowedText(cExitContentPos, Text::Align::MID, FNT_M6X11, FNT_SMALL, cExitString, WHITE, BLACK));
}

void GameOverScreenState::Update(int deltaTime) {
	GameState::Update(deltaTime);

	if (_againButton->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->ChangeState(new PlayingState());
		SoundManager::Instance()->PlaySFX("GameStart");
	}
	else if (_exitButton->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->ChangeState(new TitleScreenState());
		SoundManager::Instance()->PlaySFX("ButtonSelect");
	}		
}
