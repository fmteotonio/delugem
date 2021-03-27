#include "TitleScreenState.h"

#include "../Constants.h"
#include "../Position.h"
#include "../GameObjects/ForegroundStrip.h"
#include "../GameObjects/Buttons/BigButton.h"
#include "../GameObjects/Texts/ShadowedText.h"
#include "../GameObjects/StaticImages/StaticImage.h"
#include "../Game.h"
#include "../SoundManager.h"
#include "PlayingState.h"

//........................GameObject Constants........................

const int TitleScreenState::cLeftBoardX = 0;
const int TitleScreenState::cLeftBoardY = 28;
const int TitleScreenState::cRightBoardX = 240;
const int TitleScreenState::cRightBoardY = 28;

const int TitleScreenState::cTitleX = 98;
const int TitleScreenState::cTitleY = 52;
const int TitleScreenState::cTitleW = 185;
const int TitleScreenState::cTitleH = 57;
const char* TitleScreenState::cTitlePath = "res/images/title.png";

const int TitleScreenState::cStartButtonX = SCREEN_W / 2 - BigButton::cW / 2;
const int TitleScreenState::cStartButtonY = SCREEN_H / 2 - BigButton::cH / 2 + 55;
const int TitleScreenState::cStartContentX = cStartButtonX + BigButton::cW / 2;
const int TitleScreenState::cStartContentY = cStartButtonY + BigButton::cH / 2;
const char* TitleScreenState::cStartString = "RESUME";

//........................................................................

void TitleScreenState::Init() {

	stateID_ = "TITLESCREEN";

	//Decorative Boards

	gameObjects_.push_back(leftBoard_ = new Board(cLeftBoardX, cLeftBoardY, false));
	gameObjects_.push_back(rightBoard_ = new Board(cRightBoardX, cRightBoardY, false));
	
	leftBoard_->AddNewColumns(9); rightBoard_->AddNewColumns(9);

	leftBoard_->AddGem(0, 10); rightBoard_->AddGem(8, 10);
	leftBoard_->AddGem(1, 10); rightBoard_->AddGem(7, 10);
	leftBoard_->AddGem(2, 10); rightBoard_->AddGem(6, 10);
	leftBoard_->AddGem(3, 10); rightBoard_->AddGem(5, 10);
	leftBoard_->AddGem(4,  5); rightBoard_->AddGem(4,  5);
	leftBoard_->AddGem(5,  3); rightBoard_->AddGem(3,  3);
	leftBoard_->AddGem(6,  2); rightBoard_->AddGem(2,  2);
	leftBoard_->AddGem(7,  1); rightBoard_->AddGem(1,  1);
	
	for (std::vector<Gem*> column : leftBoard_->GetBoardGems()) {
		for (Gem* gem : column) {
			gem->MoveFrom(0, (-2 * Board::cColumnSize + static_cast<int>(column.size())) * Gem::cH);
		}
	}
	for (std::vector<Gem*> column : rightBoard_->GetBoardGems()) {
		for (Gem* gem : column) {
			gem->MoveFrom(0, (-2 * Board::cColumnSize + static_cast<int>(column.size())) * Gem::cH);
		}
	}

	//Title Image

	gameObjects_.push_back(new StaticImage(cTitleX, cTitleY, cTitleW, cTitleH, cTitlePath));

	//Foreground Strips

	gameObjects_.push_back(new ForegroundStrip(0, 0));
	gameObjects_.push_back(new ForegroundStrip(0, SCREEN_H- ForegroundStrip::cH));

	//Start Game Button

	gameObjects_.push_back(playButton_ = new BigButton(cStartButtonX, cStartButtonY));
	playButton_->AddContent(new ShadowedText(cStartContentX, cStartContentY, Text::Align::MID, FNT_M6X11, 16, cStartString, WHITE, BLACK));

}

void TitleScreenState::Update(int deltaTime) {
	
	GameState::Update(deltaTime);
	
	if (!leftBoard_->GetBoardGems().at(0).at(0)->isMoving() && !hasPlayedSound_) {
		SoundManager::Instance()->PlaySFX("GemsFallTitle", false);
		hasPlayedSound_ = true;
	}
	
	if (playButton_->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->ChangeState(new PlayingState());
		SoundManager::Instance()->PlaySFX("GameStart", false);
	}

	

}