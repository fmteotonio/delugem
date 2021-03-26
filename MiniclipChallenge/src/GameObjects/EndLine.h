#pragma once

#include "AnimatedGameObject.h"

class EndLine : public AnimatedGameObject {
public:
	static const char* cPath;
	static const int cW;
	static const int cH;

	EndLine(float x, float y);
};