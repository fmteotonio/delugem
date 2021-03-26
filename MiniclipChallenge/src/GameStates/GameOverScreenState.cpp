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


void GameOverScreenState::Init() {

	stateID_ = "GAMEOVERSCREEN";

	gameObjects_.push_back(new ForegroundStrip(0, 0));
	gameObjects_.push_back(new ForegroundStrip(0, SCREEN_H- ForegroundStrip::cH));

	gameObjects_.push_back(new ShadowedText(SCREEN_W/2, SCREEN_H/2-50, Text::Align::MID, FNT_M6X11, 32, "GAME OVER", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(SCREEN_W / 2, SCREEN_H / 2 - 30, Text::Align::MID, FNT_M3X6, 16, "The Gems win this time.", WHITE, BLACK));
	
	float bXR = SCREEN_W / 2 - 60 - BigButton::cW /2;
	float bXE = SCREEN_W / 2 + 60 - BigButton::cW /2;
	float bY = 140;

	gameObjects_.push_back(playAgainButton_ = new BigButton(bXR, bY));
	playAgainButton_->AddContent(new ShadowedText(bXR + BigButton::cW / 2, bY + BigButton::cH / 2, Text::Align::MID, FNT_M6X11, 16, "PLAY AGAIN", WHITE, BLACK));
	
	gameObjects_.push_back(new ShadowedText(SCREEN_W / 2, 110, Text::Align::MID, FNT_M6X11, 16, "FINAL SCORE: "+ std::to_string(GameManager::Instance()->GetScore()), WHITE, BLACK));

	gameObjects_.push_back(exitButton_ = new BigButton(bXE, bY));
	exitButton_->AddContent(new ShadowedText(bXE + BigButton::cW / 2, bY + BigButton::cH / 2, Text::Align::MID, FNT_M6X11, 16, "EXIT GAME", WHITE, BLACK));
}

void GameOverScreenState::Update(int deltaTime) {
	GameState::Update(deltaTime);

	if (playAgainButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->ChangeState(new PlayingState());
		SoundManager::Instance()->PlaySFX("GameStart",false);
		return;
	}
	if (exitButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION)
		Game::Instance()->GetGameStateMachine()->ChangeState(new TitleScreenState());
}
