#pragma once

#include "AnimatedGameObject.h"

class EndLine : public AnimatedGameObject {
public:

	static const char* cPath;
	static const Dimensions cDim;

	static const char* cAnimDefault;

	EndLine(Position pos);

};