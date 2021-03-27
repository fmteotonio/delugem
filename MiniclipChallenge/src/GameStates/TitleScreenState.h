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
	static const int cLeftBoardX;
	static const int cLeftBoardY;
	static const int cRightBoardX;
	static const int cRightBoardY;

	static const int cTitleX;
	static const int cTitleY;
	static const int cTitleW;
	static const int cTitleH;
	static const char* cTitlePath;

	static const int cStartButtonX;
	static const int cStartButtonY;
	static const int cStartContentX;
	static const int cStartContentY;
	static const char* cStartString;

	Button* playButton_;
	Button* howButton_;

	Board* leftBoard_;
	Board* rightBoard_;
	
	bool hasPlayedSound_ = false;

	void SetupTitleAnimation();
};