#pragma once

#include "GameState.h"
#include "../GameObjects/Board.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Buttons/Button.h"

class TitleScreenState : public GameState {
public:

	void Init();
	void Update(int deltaTime);

private:

	static const Position cLeftBoardPos;
	static const Position cRightBoardPos;
	static const Position cUpperStripPos;
	static const Position cLowerStripPos;

	static const Position cTitlePos;
	static const Position cStartButtonPos;
	static const Position cStartContentPos;
	static const Position cExitButtonPos;
	static const Position cExitContentPos;
	static const char* cExitContentPath;
	
	static const Dimensions cTitleDim;
	static const char* cTitlePath;

	static const char* cStartString;

	Board* _leftBoard;
	Board* _rightBoard;

	Button* _playButton;
	Button* _exitButton;

	bool _hasPlayedSound = false;

};