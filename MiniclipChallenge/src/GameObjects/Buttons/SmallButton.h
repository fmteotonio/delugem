#pragma once

#include "Button.h"

class SmallButton : public Button {
public:
	static const char* cPath;
	static const int cW;
	static const int cH;

	SmallButton(float x, float y) : Button(x, y, cW, cH, cPath) {}
};