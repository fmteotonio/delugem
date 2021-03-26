#include "TitleScreenState.h"

#include "../Constants.h"
#include "../GameObjects/ForegroundStrip.h"
#include "../GameObjects/Buttons/BigButton.h"
#include "../GameObjects/Texts/ShadowedText.h"
#include "../Game.h"
#include "../GameManager.h"
#include "../SoundManager.h"
#include "PlayingState.h"

void TitleScreenState::Init() {

	stateID_ = "TITLESCREEN";

	GameManager::Instance()->Reset();

	gameObjects_.push_back(new ForegroundStrip(0, 0));
	gameObjects_.push_back(new ForegroundStrip(0, SCREEN_H- ForegroundStrip::cH));
	
	int bX = SCREEN_W / 2 - BigButton::cW / 2;
	int bY = SCREEN_H / 2 - BigButton::cH / 2;
	int bW = BigButton::cW;
	int bH = BigButton::cH;

	gameObjects_.push_back(playButton_ = new BigButton(bX, bY));
	playButton_->AddContent(new ShadowedText(bX + bW / 2, bY + bH / 2, Text::Align::MID, FNT_M6X11, 16, "START GAME!", WHITE, BLACK));
}

void TitleScreenState::Update(int deltaTime) {
	GameState::Update(deltaTime);

	if (playButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->ChangeState(new PlayingState());
		SoundManager::Instance()->PlaySFX("GameStart", false);
	}
		
}
