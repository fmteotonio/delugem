#include "PauseScreenState.h"

#include "PlayingState.h"
#include "TitleScreenState.h"
#include "../gameObjects/buttons/BigButton.h"
#include "../gameObjects/texts/ShadowedText.h"
#include "../gameObjects/Background.h"
#include "../gameObjects/ForegroundStrip.h"
#include "../Constants.h"
#include "../Game.h"
#include "../GameManager.h"
#include "../SoundManager.h"

//........................GameObject Constants........................

const Position PauseScreenState::cUpperStripPos = { 0,  0 };
const Position PauseScreenState::cLowerStripPos = { 0, SCREEN_H - ForegroundStrip::cDestDim.h };

const Position PauseScreenState::cPausedTextPos = { SCREEN_W / 2 , SCREEN_H / 2 - 50 };
const Position PauseScreenState::cFlavorTextPos = { SCREEN_W / 2 , SCREEN_H / 2 - 30 };
const Position PauseScreenState::cScoreTextPos =  { SCREEN_W / 2 , 110 };

const Position PauseScreenState::cResumeButtonPos  = { SCREEN_W / 2 - BigButton::cDim.w / 2 - 60 , 140 };
const Position PauseScreenState::cExitButtonPos    = { SCREEN_W / 2 - BigButton::cDim.w / 2 + 60 , 140 };
const Position PauseScreenState::cResumeContentPos = { cResumeButtonPos.x + BigButton::cDim.w / 2 , cResumeButtonPos.y + BigButton::cDim.h / 2 };
const Position PauseScreenState::cExitContentPos   = { cExitButtonPos.x + BigButton::cDim.w / 2 , cExitButtonPos.y + BigButton::cDim.h / 2 };

const char* PauseScreenState::cPausedString = "GAME PAUSED";
const char* PauseScreenState::cFlavorString = "The Gems don't mind waiting.";
const char* PauseScreenState::cScorePartialString = "CURRENT SCORE: ";
const char* PauseScreenState::cResumeString = "RESUME";
const char* PauseScreenState::cExitString = "EXIT GAME";

//........................................................................

void PauseScreenState::Init() {

	stateID_ = "PAUSESCREEN";

	//Background & Foreground Strips

	_gameObjects.push_back(new Background());
	_gameObjects.push_back(new ForegroundStrip(cUpperStripPos));
	_gameObjects.push_back(new ForegroundStrip(cLowerStripPos));

	//Text to be displayed;

	std::string scoreString  = cScorePartialString + std::to_string(GameManager::Instance()->GetScore());

	_gameObjects.push_back(new ShadowedText(cPausedTextPos, Text::Align::MID, FNT_M6X11, FNT_LARGE, cPausedString, WHITE, BLACK));
	_gameObjects.push_back(new ShadowedText(cFlavorTextPos, Text::Align::MID, FNT_M3X6, FNT_SMALL, cFlavorString, WHITE, BLACK));
	_gameObjects.push_back(new ShadowedText(cScoreTextPos, Text::Align::MID, FNT_M6X11, FNT_SMALL, scoreString, WHITE, BLACK));

	//Resume and Exit Buttons
	
	_gameObjects.push_back(_resumeButton = new BigButton(cResumeButtonPos));
	_gameObjects.push_back(_exitButton = new BigButton(cExitButtonPos));
	
	_resumeButton->AddContent(new ShadowedText(cResumeContentPos, Text::Align::MID, FNT_M6X11, FNT_SMALL, cResumeString, WHITE, BLACK));
	_exitButton->AddContent(new ShadowedText(cExitContentPos, Text::Align::MID, FNT_M6X11, FNT_SMALL, cExitString, WHITE, BLACK));
}

void PauseScreenState::Update(int deltaTime) {
	GameState::Update(deltaTime);

	if (_resumeButton->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->PopState();
		SoundManager::Instance()->PlaySFX("ButtonSelect");
	}
		
	else if (_exitButton->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		SoundManager::Instance()->StopMusic();
		Game::Instance()->GetGameStateMachine()->ChangeState(new TitleScreenState());
		SoundManager::Instance()->PlaySFX("ButtonSelect");
	}
}