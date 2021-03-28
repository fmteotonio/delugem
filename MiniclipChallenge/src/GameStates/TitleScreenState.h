#pragma once

#include "GameState.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Buttons/Button.h"
#include "../GameObjects/Board.h"

#include <vector>

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
	
	static const int cTitleW;
	static const int cTitleH;
	static const char* cTitlePath;

	static const char* cStartString;

	Board* leftBoard_;
	Board* rightBoard_;

	Button* playButton_;
	Button* howButton_;

	bool hasPlayedSound_ = false;

};