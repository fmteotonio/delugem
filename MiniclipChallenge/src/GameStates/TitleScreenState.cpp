#include "TitleScreenState.h"

#include "../Constants.h"
#include "../GameObjects/ForegroundStrip.h"
#include "../GameObjects/Buttons/BigButton.h"
#include "../GameObjects/Texts/ShadowedText.h"
#include "../Game.h"
#include "../GameManager.h"
#include "../SoundManager.h"
#include "../GameObjects/StaticImages/StaticImage.h"
#include "PlayingState.h"

const int TitleScreenState::cStartButtonX = SCREEN_W / 2 - BigButton::cW / 2;
const int TitleScreenState::cStartButtonY = SCREEN_H / 2 - BigButton::cH / 2 + 10;

void TitleScreenState::Init() {

	stateID_ = "TITLESCREEN";

	//Decorative Boards
	gameObjects_.push_back(board1_ = new Board(0, 28, false));
	gameObjects_.push_back(board2_ = new Board(240, 28, false));
	
	for (int i = 0; i < 9; ++i) {
		board1_->AddColumn();
		board2_->AddColumn();
	}
	for (int i = 0; i < 10; ++i) {
		board1_->AddGem(0); board2_->AddGem(8);
		board1_->AddGem(1); board2_->AddGem(7);
		board1_->AddGem(2); board2_->AddGem(6);
		board1_->AddGem(3); board2_->AddGem(5);
	}
	for (int i = 0; i < 5; ++i) {
		board1_->AddGem(4); board2_->AddGem(4);
	}

	board1_->AddGem(5); board1_->AddGem(5); board1_->AddGem(5);
	board2_->AddGem(3); board2_->AddGem(3); board2_->AddGem(3);

	board1_->AddGem(6); board1_->AddGem(6);
	board2_->AddGem(2); board2_->AddGem(2);

	board1_->AddGem(7);
	board2_->AddGem(1);



	for (std::vector<Gem*> column : board1_->boardGems_) {
		for (Gem* gem : column) {
			gem->SetY(gem->GetY() - 10 * Gem::cH - ((10 - column.size()) * Gem::cH));
			gem->Move(0, 10 * Gem::cH + ((10 - column.size()) * Gem::cH));
		}
	}
	for (std::vector<Gem*> column : board2_->boardGems_) {
		for (Gem* gem : column) {
			gem->SetY(gem->GetY() - 10 * Gem::cH - ((10 - column.size()) * Gem::cH));
			gem->Move(0, 10 * Gem::cH + ((10 - column.size()) * Gem::cH));
		}
	}



	gameObjects_.push_back(new StaticImage(98, 52, 185, 57, "res/images/title.png" ));

	//Foreground Strips

	gameObjects_.push_back(new ForegroundStrip(0, 0));
	gameObjects_.push_back(new ForegroundStrip(0, SCREEN_H- ForegroundStrip::cH));

	//Start Game Button

	gameObjects_.push_back(playButton_ = new BigButton(cStartButtonX, cStartButtonY+25));
	//gameObjects_.push_back(howButton_ = new BigButton(cStartButtonX, cStartButtonY+40));
	
	std::string startString = "START GAME!";

	int startContentX = cStartButtonX + BigButton::cW / 2;
	int startContentY = cStartButtonY + BigButton::cH / 2;

	playButton_->AddContent(new ShadowedText(startContentX, startContentY+25, Text::Align::MID, FNT_M6X11, 16, startString, WHITE, BLACK));
	//howButton_->AddContent(new ShadowedText(startContentX, startContentY+40, Text::Align::MID, FNT_M6X11, 16, "HOW TO PLAY", WHITE, BLACK));
}

void TitleScreenState::Update(int deltaTime) {
	
	GameState::Update(deltaTime);
	
	if (!board1_->boardGems_.at(0).at(0)->isMoving() && !hasPlayedSound_) {
		SoundManager::Instance()->PlaySFX("GemsFallTitle", false);
		hasPlayedSound_ = true;
	}
	
	if (playButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->ChangeState(new PlayingState());
		SoundManager::Instance()->PlaySFX("GameStart", false);
	}

	

}

void TitleScreenState::SetupTitleAnimation() {

}