#pragma once

#include "Button.h"

class BigButton : public Button {
public:
	static const char* cPath;
	static const int cW;
	static const int cH;

	BigButton(float x, float y) : Button(x, y, cW, cH, cPath) {}
};