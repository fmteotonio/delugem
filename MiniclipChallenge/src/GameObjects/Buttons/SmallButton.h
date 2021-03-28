#pragma once

#include "Button.h"

class SmallButton : public Button {
public:
	static const char* cPath;
	static const int cW;
	static const int cH;

	SmallButton(Position pos) : Button(pos, cW, cH, cPath) {}
};