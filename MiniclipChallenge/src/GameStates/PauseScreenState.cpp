#include "PauseScreenState.h"

#include "../Constants.h"
#include "../GameObjects/ForegroundStrip.h"
#include "../GameObjects/Buttons/BigButton.h"
#include "../GameObjects/Texts/ShadowedText.h"
#include "../Game.h"
#include "../GameManager.h"
#include "PlayingState.h"
#include "TitleScreenState.h"

void PauseScreenState::Init() {

	stateID_ = "PAUSESCREEN";

	gameObjects_.push_back(new ForegroundStrip(0, 0));
	gameObjects_.push_back(new ForegroundStrip(0, SCREEN_H- ForegroundStrip::cH));

	gameObjects_.push_back(new ShadowedText(SCREEN_W/2, SCREEN_H/2-50, Text::Align::MID, FNT_M6X11, 32, "GAME PAUSED", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(SCREEN_W / 2, SCREEN_H / 2 - 30, Text::Align::MID, FNT_M3X6, 16, "The Gems don't mind waiting.", WHITE, BLACK));
	
	float bXR = SCREEN_W / 2 - 60 - BigButton::cW / 2;
	float bXE = SCREEN_W / 2 + 60 - BigButton::cW / 2;
	float bY = 140;
	gameObjects_.push_back(resumeButton_ = new BigButton(bXR, bY));
	resumeButton_->AddContent(new ShadowedText(bXR + BigButton::cW / 2, bY + BigButton::cH / 2, Text::Align::MID, FNT_M6X11, 16, "RESUME", WHITE, BLACK));


	gameObjects_.push_back(new ShadowedText(SCREEN_W / 2, 110, Text::Align::MID, FNT_M6X11, 16, "CURRENT SCORE: " + std::to_string(GameManager::Instance()->GetScore()), WHITE, BLACK));

	
	gameObjects_.push_back(exitButton_ = new BigButton(bXE, bY));
	exitButton_->AddContent(new ShadowedText(bXE + BigButton::cW / 2, bY + BigButton::cH / 2, Text::Align::MID, FNT_M6X11, 16, "EXIT GAME", WHITE, BLACK));
}

void PauseScreenState::Update(int deltaTime) {
	GameState::Update(deltaTime);

	if (resumeButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->PopState();
		return;
	}
	if (exitButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION)
		Game::Instance()->GetGameStateMachine()->ChangeState(new TitleScreenState());
}