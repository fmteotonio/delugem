#pragma once

#include "GameState.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Buttons/Button.h"
#include "../GameObjects/Board.h"
#include "../GameObjects/ForegroundStrip.h"

#include <string>
#include <vector>

class PlayingState : public GameState {
public:
	static const int cBoardX;
	static const int cBoardY;
	static const int cEndLineX;
	static const int cEndLineY;

	static const char* cFillPath;
	static const char* cPausePath;
	static const char* cPushPath;

	void Init();
	void Update(int deltaTime);
	void Render();
	void Clean();

private:
	int displayedScore_;
	int displayedLevel_;
	int displayedFills_;
	GameObject* scoreValueText_;
	GameObject* levelValueText_;	
	GameObject* fillsText_;
	
	Board* board_;
	Button* pauseButton_;
	Button* pushButton_;
	Button* fillButton_;

	ForegroundStrip* foregroundStrip1_;
	ForegroundStrip* foregroundStrip2_;
};