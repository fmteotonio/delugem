#pragma once

#include <string>

#include "../AnimatedGameObject.h"

class StaticImage : public AnimatedGameObject {
public:

	static const char* cAnimDefault;

	StaticImage(Position pos, Dimensions dim, std::string filename);

};