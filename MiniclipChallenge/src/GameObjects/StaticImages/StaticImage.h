#pragma once

#include "../AnimatedGameObject.h"

#include <string>

class StaticImage : public AnimatedGameObject {
public:
	StaticImage(Position pos, int w, int h, std::string filename);
};