#pragma once

#include "Button.h"

class BigButton : public Button {
public:
	static const char* cPath;
	static const int cW;
	static const int cH;

	BigButton(Position pos) : Button(pos, cW, cH, cPath) {}
};