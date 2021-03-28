#include "PauseScreenState.h"

#include "PlayingState.h"
#include "TitleScreenState.h"
#include "../GameObjects/ForegroundStrip.h"
#include "../GameObjects/Buttons/BigButton.h"
#include "../GameObjects/Texts/ShadowedText.h"
#include "../Constants.h"
#include "../Game.h"
#include "../GameManager.h"
#include "../SoundManager.h"

//........................GameObject Constants........................

const Position PauseScreenState::cUpperStripPos = { 0,  0 };
const Position PauseScreenState::cLowerStripPos = { 0, SCREEN_H - ForegroundStrip::cH };

const Position PauseScreenState::cPausedTextPos = { SCREEN_W / 2 , SCREEN_H / 2 - 50 };
const Position PauseScreenState::cFlavorTextPos = { SCREEN_W / 2 , SCREEN_H / 2 - 30 };
const Position PauseScreenState::cScoreTextPos =  { SCREEN_W / 2 , 110 };

const Position PauseScreenState::cResumeButtonPos  = { SCREEN_W / 2 - BigButton::cW / 2 - 60 , 140 };
const Position PauseScreenState::cExitButtonPos    = { SCREEN_W / 2 - BigButton::cW / 2 + 60 , 140 };
const Position PauseScreenState::cResumeContentPos = { cResumeButtonPos.x + BigButton::cW / 2 , cResumeButtonPos.y + BigButton::cH / 2 };
const Position PauseScreenState::cExitContentPos   = { cExitButtonPos.x + BigButton::cW / 2 , cExitButtonPos.y + BigButton::cH / 2 };

const char* PauseScreenState::cPausedString = "GAME PAUSED";
const char* PauseScreenState::cFlavorString = "The Gems don't mind waiting.";
const char* PauseScreenState::cResumeString = "RESUME";
const char* PauseScreenState::cExitString = "EXIT GAME";

//........................................................................

void PauseScreenState::Init() {

	stateID_ = "PAUSESCREEN";

	//Foreground Strips

	gameObjects_.push_back(new ForegroundStrip(cUpperStripPos));
	gameObjects_.push_back(new ForegroundStrip(cLowerStripPos));

	//Text to be displayed;

	std::string scoreString  = "CURRENT SCORE: " + std::to_string(GameManager::Instance()->GetScore());

	gameObjects_.push_back(new ShadowedText(cPausedTextPos, Text::Align::MID, FNT_M6X11, 32, cPausedString, WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(cFlavorTextPos, Text::Align::MID, FNT_M3X6, 16, cFlavorString, WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(cScoreTextPos, Text::Align::MID, FNT_M6X11, 16, scoreString, WHITE, BLACK));

	//Resume and Exit Buttons
	
	gameObjects_.push_back(resumeButton_ = new BigButton(cResumeButtonPos));
	gameObjects_.push_back(exitButton_ = new BigButton(cExitButtonPos));
	
	resumeButton_->AddContent(new ShadowedText(cResumeContentPos, Text::Align::MID, FNT_M6X11, 16, cResumeString, WHITE, BLACK));
	exitButton_->AddContent(new ShadowedText(cExitContentPos, Text::Align::MID, FNT_M6X11, 16, cExitString, WHITE, BLACK));
}

void PauseScreenState::Update(int deltaTime) {

	GameState::Update(deltaTime);

	if (resumeButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->PopState();
		SoundManager::Instance()->PlaySFX("ButtonSelect", false);
	}
		
	else if (exitButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->ChangeState(new TitleScreenState());
		SoundManager::Instance()->PlaySFX("ButtonSelect", false);
	}
		
}