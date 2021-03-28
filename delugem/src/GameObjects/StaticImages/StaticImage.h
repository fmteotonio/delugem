#pragma once

#include <string>

#include "../AnimatedGameObject.h"

class StaticImage : public AnimatedGameObject {
public:
	StaticImage(Position pos, Dimensions dim, std::string filename);
};