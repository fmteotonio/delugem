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
	gameObjects_.push_back(new ForegroundStrip(0, SCREEN_HEIGHT- ForegroundStrip::cH));

	gameObjects_.push_back(new ShadowedText(SCREEN_WIDTH/2, SCREEN_HEIGHT/2-50, Text::Align::MID, FNT_M6X11, 32, "GAME OVER", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 30, Text::Align::MID, FNT_M3X6, 16, "The Gems always win in the end.", WHITE, BLACK));
	
	float bXR = SCREEN_WIDTH / 2 - 60 - BigButton::cW /2;
	float bXE = SCREEN_WIDTH / 2 + 60 - BigButton::cW /2;
	float bY = 140;

	gameObjects_.push_back(playAgainButton_ = new BigButton(bXR, bY));
	playAgainButton_->AddContent(new ShadowedText(bXR + BigButton::cW / 2, bY + BigButton::cH / 2, Text::Align::MID, FNT_M6X11, 16, "PLAY AGAIN", WHITE, BLACK));
	
	gameObjects_.push_back(new ShadowedText(SCREEN_WIDTH / 2, 110, Text::Align::MID, FNT_M6X11, 16, "FINAL SCORE: "+ std::to_string(GameManager::Instance()->score()), WHITE, BLACK));

	gameObjects_.push_back(exitButton_ = new BigButton(bXE, bY));
	exitButton_->AddContent(new ShadowedText(bXE + BigButton::cW / 2, bY + BigButton::cH / 2, Text::Align::MID, FNT_M6X11, 16, "EXIT GAME", WHITE, BLACK));
}

void GameOverScreenState::Update(int deltaTime) {
	GameState::Update(deltaTime);

	if (playAgainButton_->buttonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->gameStateMachine()->changeState(new PlayingState());
		SoundManager::Instance()->playSFX("GameStart",false);
		return;
	}
	if (exitButton_->buttonState() == Button::ButtonState::PRESS_ACTION)
		Game::Instance()->gameStateMachine()->changeState(new TitleScreenState());
}
