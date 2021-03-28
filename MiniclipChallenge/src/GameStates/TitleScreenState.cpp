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

const Position TitleScreenState::cLeftBoardPos  = {   0, 28 };
const Position TitleScreenState::cRightBoardPos = { 240, 28 };
const Position TitleScreenState::cUpperStripPos = {   0,  0 };
const Position TitleScreenState::cLowerStripPos = {   0, SCREEN_H - ForegroundStrip::cDim.h };

const Position TitleScreenState::cTitlePos = { 98, 52 };
const Position TitleScreenState::cStartButtonPos = { SCREEN_W / 2 - BigButton::cDim.w / 2 , 126 };
const Position TitleScreenState::cStartContentPos = { cStartButtonPos.x + BigButton::cDim.w / 2, cStartButtonPos.y + BigButton::cDim.h / 2 };


const Dimensions TitleScreenState::cTitleDim = { 185,57 };


const char* TitleScreenState::cTitlePath = "res/images/title.png";

const char* TitleScreenState::cStartString = "START GAME!";

//........................................................................

void TitleScreenState::Init() {

	stateID_ = "TITLESCREEN";

	//Decorative Boards
	gameObjects_.push_back(leftBoard_ = new Board(cLeftBoardPos, false));
	gameObjects_.push_back(rightBoard_ = new Board(cRightBoardPos, false));

	leftBoard_->AddNewColumns(9);	rightBoard_->AddNewColumns(9);
	leftBoard_->AddGem(0, 10);		rightBoard_->AddGem(8, 10);
	leftBoard_->AddGem(1, 10);		rightBoard_->AddGem(7, 10);
	leftBoard_->AddGem(2, 10);		rightBoard_->AddGem(6, 10);
	leftBoard_->AddGem(3, 10);		rightBoard_->AddGem(5, 10);
	leftBoard_->AddGem(4, 5);		rightBoard_->AddGem(4, 5);
	leftBoard_->AddGem(5, 3);		rightBoard_->AddGem(3, 3);
	leftBoard_->AddGem(6, 2);		rightBoard_->AddGem(2, 2);
	leftBoard_->AddGem(7, 1);		rightBoard_->AddGem(1, 1);

	for (std::vector<Gem*> column : leftBoard_->GetBoardGems()) {
		for (Gem* gem : column) {
			gem->MoveFrom(0, (-2 * Board::cColumnSize + static_cast<int>(column.size())) * Gem::cDim.h);
		}
	}
	for (std::vector<Gem*> column : rightBoard_->GetBoardGems()) {
		for (Gem* gem : column) {
			gem->MoveFrom(0, (-2 * Board::cColumnSize + static_cast<int>(column.size())) * Gem::cDim.h);
		}
	}

	//Title Image
	gameObjects_.push_back(new StaticImage(cTitlePos, cTitleDim, cTitlePath));

	//Foreground Strips
	gameObjects_.push_back(new ForegroundStrip(cUpperStripPos));
	gameObjects_.push_back(new ForegroundStrip(cLowerStripPos));

	//Start Button
	gameObjects_.push_back(playButton_ = new BigButton(cStartButtonPos));
	playButton_->AddContent(new ShadowedText(cStartContentPos, Text::Align::MID, FNT_M6X11, 16, cStartString, WHITE, BLACK));

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