#include "TitleScreenState.h"

#include "../Constants.h"
#include "../structs/Position.h"
#include "../gameObjects/ForegroundStrip.h"
#include "../gameObjects/buttons/BigButton.h"
#include "../gameObjects/buttons/SmallButton.h"
#include "../gameObjects/texts/ShadowedText.h"
#include "../gameObjects/staticImages/StaticImage.h"
#include "../gameObjects/staticImages/SmallIcon.h"
#include "../Game.h"
#include "../SoundManager.h"
#include "PlayingState.h"

//........................GameObject Constants........................

const Position TitleScreenState::cLeftBoardPos  = {   0, 28 };
const Position TitleScreenState::cRightBoardPos = { 240, 28 };
const int      TitleScreenState::cBoardColumns  = 10;
const Position TitleScreenState::cUpperStripPos = {   0,  0 };
const Position TitleScreenState::cLowerStripPos = {   0, SCREEN_H - ForegroundStrip::cDestDim.h };

const Position TitleScreenState::cTitlePos = { 98, 52 };
const Position TitleScreenState::cStartButtonPos = { SCREEN_W / 2 - BigButton::cDim.w / 2 , 126 };
const Position TitleScreenState::cStartContentPos = { cStartButtonPos.x + BigButton::cDim.w / 2, cStartButtonPos.y + BigButton::cDim.h / 2 };

const Position TitleScreenState::cExitButtonPos = { 351 , 2 };
const Position TitleScreenState::cExitContentPos = { cExitButtonPos.x + 8 , cExitButtonPos.y + 8 };
const char* TitleScreenState::cExitContentPath = "res/images/iconexit.png";

const Dimensions TitleScreenState::cTitleDim = { 185,57 };
const char* TitleScreenState::cTitlePath = "res/images/title.png";

const char* TitleScreenState::cStartString = "START GAME!";

//........................................................................

void TitleScreenState::Init() {

	stateID_ = "TITLESCREEN";

	//Decorative Boards

	_gameObjects.push_back(_leftBoard = new Board(cLeftBoardPos, cBoardColumns, false));
	_gameObjects.push_back(_rightBoard = new Board(cRightBoardPos, cBoardColumns, false));

	_leftBoard->AddNewColumns(9);	_rightBoard->AddNewColumns(9);
	_leftBoard->AddGems(0, 10);		_rightBoard->AddGems(8, 10);
	_leftBoard->AddGems(1, 10);		_rightBoard->AddGems(7, 10);
	_leftBoard->AddGems(2, 10);		_rightBoard->AddGems(6, 10);
	_leftBoard->AddGems(3, 10);		_rightBoard->AddGems(5, 10);
	_leftBoard->AddGems(4, 5);		_rightBoard->AddGems(4, 5);
	_leftBoard->AddGems(5, 3);		_rightBoard->AddGems(3, 3);
	_leftBoard->AddGems(6, 2);		_rightBoard->AddGems(2, 2);
	_leftBoard->AddGems(7, 1);		_rightBoard->AddGems(1, 1);

	for (std::vector<Gem*> column : _leftBoard->GetBoardGems()) {
		for (Gem* gem : column) {
			gem->MoveFrom({ 0, 
				static_cast<float>((-2 * cBoardColumns + static_cast<int>(column.size())) * Gem::cDim.h) });
		}
	}
	for (std::vector<Gem*> column : _rightBoard->GetBoardGems()) {
		for (Gem* gem : column) {
			gem->MoveFrom({ 0, static_cast<float>((-2 * cBoardColumns + static_cast<int>(column.size())) * Gem::cDim.h) });
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

	//Exit Button
	_gameObjects.push_back(_exitButton = new SmallButton(cExitButtonPos));
	_exitButton->AddContent(new SmallIcon(cExitContentPos, cExitContentPath));
}

void TitleScreenState::Update(int deltaTime) {
	
	GameState::Update(deltaTime);
	
	if (!_leftBoard->GetBoardGems().at(0).at(0)->isMoving(false,true) && !_hasPlayedSound) {
		SoundManager::Instance()->PlaySFX("GemsFallTitle");
		_hasPlayedSound = true;
	}
	
	if (_playButton->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->GetGameStateMachine()->ChangeState(new PlayingState());
		SoundManager::Instance()->PlaySFX("GameStart");
	}
	else if (_exitButton->GetButtonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->Quit();
	}
}