#pragma once

namespace UI {

	static const int cTopTextY = 14;
	static const int cBotTextY = 202;
	static const int cTopButtonY = cTopTextY - 12;
	static const int cBotButtonY = cBotTextY - 12;

	static const Position cLevelTextPos  = {   7,  cTopTextY };
	static const Position cScoreTextPos  = { 165,  cTopTextY };
	static const Position cPushTextPos   = { 313,  cBotTextY };
	static const Position cFillsTextPos  = {   7,  cBotTextY };
	static const Position cFillsText2Pos = { cFillsTextPos.x + 50, cBotTextY };

	static const Position cLevelValuePos = { cLevelTextPos.x + 71 , cTopTextY };
	static const Position cScoreValuePos = { cScoreTextPos.x + 99 , cTopTextY };
	static const Position cFillsValuePos = { cFillsTextPos.x + 38 , cBotTextY };

	static const Position cPauseButtonPos = { 351 , cTopButtonY };
	static const Position cFillsButtonPos = { cFillsTextPos.x + 91, cBotButtonY };
	static const Position cPushButtonPos =  { cPushTextPos.x + 38 , cBotButtonY };

	static const Position cPauseContentPos = { cPauseButtonPos.x + 8 , cPauseButtonPos.y + 8 };
	static const Position cFillsContentPos = { cFillsButtonPos.x + 8, cFillsButtonPos.y + 8 };
	static const Position cPushContentPos =  { cPushButtonPos.x + 8 , cPushButtonPos.y + 8 };

	static const char* cFillIconPath = "res/images/iconfill.png";
	static const char* cPauseIconPath = "res/images/iconpause.png";
	static const char* cPushIconPath = "res/images/iconpush.png";
}