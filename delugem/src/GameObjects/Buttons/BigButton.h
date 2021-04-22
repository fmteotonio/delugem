#pragma once

#include "Button.h"

class BigButton : public Button {
public:

	static const char* cPath;
	static const Dimensions cDim;

	BigButton(Position pos) : Button(pos, cDim, cPath) {}

};