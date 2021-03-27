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

const int PauseScreenState::cPausedTextX   = SCREEN_W / 2;
const int PauseScreenState::cPausedTextY   = SCREEN_H / 2 - 50;
const char* PauseScreenState::cPausedString = "GAME PAUSED";

const int PauseScreenState::cFlavorTextX   = SCREEN_W / 2;
const int PauseScreenState::cFlavorTextY   = SCREEN_H / 2 - 30;
const char* PauseScreenState::cFlavorString = "The Gems don't mind waiting.";

const int PauseScreenState::cScoreTextX    = SCREEN_W / 2;
const int PauseScreenState::cScoreTextY	   = 110;

const int PauseScreenState::cResumeButtonX = SCREEN_W / 2 - 60 - BigButton::cW / 2;
const int PauseScreenState::cResumeButtonY = 140;
const int PauseScreenState::cResumeContentX = cResumeButtonX + BigButton::cW / 2;
const int PauseScreenState::cResumeContentY = cResumeButtonY + BigButton::cH / 2;
const char* PauseScreenState::cResumeString = "RESUME";

const int PauseScreenState::cExitButtonX   = SCREEN_W / 2 + 60 - BigButton::cW / 2;
const int PauseScreenState::cExitButtonY   = 140;
const int PauseScreenState::cExitContentX = cExitButtonX + BigButton::cW / 2;
const int PauseScreenState::cExitContentY = cExitButtonY + BigButton::cH / 2;
const char* PauseScreenState::cExitString = "EXIT GAME";

void PauseScreenState::Init() {

	stateID_ = "PAUSESCREEN";

	//Foreground Strips

	gameObjects_.push_back(new ForegroundStrip(0, 0));
	gameObjects_.push_back(new ForegroundStrip(0, SCREEN_H- ForegroundStrip::cH));

	//Text to be displayed;

	std::string scoreString  = "CURRENT SCORE: " + std::to_string(GameManager::Instance()->GetScore());

	gameObjects_.push_back(new ShadowedText(cPausedTextX, cPausedTextY, Text::Align::MID, FNT_M6X11, 32, cPausedString, WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(cFlavorTextX, cFlavorTextY, Text::Align::MID, FNT_M3X6, 16, cFlavorString, WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(cScoreTextX, cScoreTextY, Text::Align::MID, FNT_M6X11, 16, scoreString, WHITE, BLACK));

	//Resume and Exit Buttons
	
	gameObjects_.push_back(resumeButton_ = new BigButton(cResumeButtonX, cResumeButtonY));
	gameObjects_.push_back(exitButton_ =   new BigButton(cExitButtonX, cExitButtonY));
	
	resumeButton_->AddContent(new ShadowedText(cResumeContentX, cResumeContentY, Text::Align::MID, FNT_M6X11, 16, cResumeString, WHITE, BLACK));
	exitButton_->AddContent(new ShadowedText(cExitContentX, cExitContentY, Text::Align::MID, FNT_M6X11, 16, cExitString, WHITE, BLACK));
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