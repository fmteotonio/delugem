#pragma once

#include "GameState.h"
#include "../gameObjects/buttons/Button.h"
#include "../gameObjects/Board.h"
#include "../gameObjects/GameObject.h"

class TitleScreenState : public GameState {
public:

	static const Position cUpperStripPos;
	static const Position cLowerStripPos;
	static const Position cLeftBoardPos;
	static const Position cRightBoardPos;

	static const Position cTitlePos;
	static const Dimensions cTitleDim;
	static const char* cTitlePath;

	static const Position cStartButtonPos;
	static const Position cStartContentPos;
	static const char* cStartString;

	static const Position cExitButtonPos;
	static const Position cExitContentPos;
	static const char* cExitContentPath;

	static const char* cID;

	void Init();
	void Update(int deltaTime);

private:
	
	bool _hasPlayedSound = false;

	Board* _leftBoard;
	Board* _rightBoard;
	Button* _playButton;
	Button* _exitButton;

	void SetupDecorBoards();

};