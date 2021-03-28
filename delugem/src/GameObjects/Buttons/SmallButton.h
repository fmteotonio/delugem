#pragma once

#include "Button.h"

class SmallButton : public Button {
public:
	static const char* cPath;
	static const Dimensions cDim;

	SmallButton(Position pos) : Button(pos, cDim, cPath) {}
};