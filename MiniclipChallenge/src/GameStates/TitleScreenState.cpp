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
	_gameObjects.push_back(_leftBoard = new Board(cLeftBoardPos, false));
	_gameObjects.push_back(_rightBoard = new Board(cRightBoardPos, false));

	_leftBoard->AddNewColumns(9);	_rightBoard->AddNewColumns(9);
	_leftBoard->AddGem(0, 10);		_rightBoard->AddGem(8, 10);
	_leftBoard->AddGem(1, 10);		_rightBoard->AddGem(7, 10);
	_leftBoard->AddGem(2, 10);		_rightBoard->AddGem(6, 10);
	_leftBoard->AddGem(3, 10);		_rightBoard->AddGem(5, 10);
	_leftBoard->AddGem(4, 5);		_rightBoard->AddGem(4, 5);
	_leftBoard->AddGem(5, 3);		_rightBoard->AddGem(3, 3);
	_leftBoard->AddGem(6, 2);		_rightBoard->AddGem(2, 2);
	_leftBoard->AddGem(7, 1);		_rightBoard->AddGem(1, 1);

	for (std::vector<Gem*> column : _leftBoard->GetBoardGems()) {
		for (Gem* gem : column) {
			gem->MoveFrom(0, (-2 * Board::cColumnSize + static_cast<int>(column.size())) * Gem::cDim.h);
		}
	}
	for (std::vector<Gem*> column : _rightBoard->GetBoardGems()) {
		for (Gem* gem : column) {
			gem->MoveFrom(0, (-2 * Board::cColumnSize + static_cast<int>(column.size())) * Gem::cDim.h);
		}
	}

	//Title Image
	_gameObjects.push_back(new StaticImage(cTitlePos, cTitleDim, cTitlePath));

	//Foreground Strips
	_gameObjects.push_back(new ForegroundStrip(cUpperStripPos));
	_gameObjects.push_back(new ForegroundStrip(cLowerStripPos));

	//Start Button
	_gameObjects.push_back(_playButton = new BigButton(cStartButtonPos));
	_playButton->AddContent(new ShadowedText(cStartContentPos, Text::Align::MID, FNT_M6X11, 16, cStartString, WHITE, BLACK));

}

void TitleScreenState::Update(int deltaTime) {
	
	GameState::Update(deltaTime);
	
	if (!_leftBoard->GetBoardGems().at(0).at(0)->isMoving() && !_hasPlayedSound) {
		SoundManager::Instance()->PlaySFX("GemsFallTitle", false);
		_hasPlayedSound = true;
	}
	
	if (_playButton->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->ChangeState(new PlayingState());
		SoundManager::Instance()->PlaySFX("GameStart", false);
	}
}